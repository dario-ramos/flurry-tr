from behave import *
import subprocess
import os
import re
import public_ips
import netifaces
import signal

@given('I am running scamper dealias from the command line using -I')
def step_impl(context):
	context.scamper_path = '../scamper/scamper'
	context.dealias_cmd = 'dealias -O inseq -W 1000 -m ally -p \'-P udp\' 192.0.2.1 192.0.2.4'
	context.public_ip = public_ips.get_public_ip()
	print(f'\tselected public IP: {context.public_ip}\n')

@when('I run the dealias scamper command in a basic usage scenario')
def step_impl(context):
	result = subprocess.run(['sudo', context.scamper_path, '-I', context.dealias_cmd], check=True, capture_output=True, text=True)
	context.stdout = result.stdout
	context.stderr = result.stderr
	context.returncode = result.returncode

@then(u'I should get a non-empty dealias response without errors')
def step_impl(context):
	assert context.stderr == '', 'expected empty stderr'
	assert context.returncode == 0, 'expected return code 0'
	assert len(context.stdout) != 0, 'expected non-empty output'

@given('I am running {scamper_command_name} from the command line using -I')
def step_impl(context, scamper_command_name):
	context.scamper_path = '../scamper/scamper'
	context.output_file_path = 'output.warts'

@when('I invoke it with the -I flag set to: {scamper_command_i_flag}')
def step_impl(context, scamper_command_i_flag):
	result = subprocess.run(['sudo', context.scamper_path, '-O', 'warts', '-o', context.output_file_path,
							'-I', scamper_command_i_flag], check=True, capture_output=True, text=True)
	context.stderr = result.stderr
	context.returncode = result.returncode

@then('I should get a non-empty output file and exit code should be zero')
def step_impl(context):
	assert context.stderr == '', 'expected empty stderr'
	assert context.returncode == 0, 'expected return code 0'
	assert os.path.getsize(context.output_file_path) > 0, 'expected output file, {context.output_file_path}, to be non-empty'
	os.remove(context.output_file_path)

@given('I am running {scamper_command} from the command line using -c')
def step_impl(context, scamper_command):
	context.scamper_path = '../scamper/scamper'
	context.scamper_command = scamper_command

@when('I run the command with an IP address obtained via {ip_selector}')
def step_impl(context, ip_selector):
	ip_selector_func = getattr(public_ips, ip_selector)
	public_ip = ip_selector_func()
	result = subprocess.run(['sudo', context.scamper_path, '-c', context.scamper_command,
			'-i', public_ip], check=True, capture_output=True, text=True)
	context.stdout = result.stdout
	context.stderr = result.stderr
	context.returncode = result.returncode

@then(u'I should get a non-empty response without errors')
def step_impl(context):
	assert context.stderr == '', f'expected empty stderr, got {context.stderr}'
	assert context.returncode == 0, 'expected return code 0'
	assert len(context.stdout) != 0, 'expected non-empty output'

@given('I am running a background process pinging the loopbacks interface\'s IP')
def step_impl(context):
	context.scamper_path = '../scamper/scamper'
	context.output_file_path = 'output.warts'

	source_ip = get_loopback_interface_ip()

	assert len(source_ip) > 0, 'expected non-empty source IP'
	context.ping_subproc = subprocess.Popen( \
		["ping", source_ip], \
		stdin=subprocess.DEVNULL, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, text=True)

	context.sniff_cmd = f'sniff -S {source_ip} -G 5 icmp[icmpid] == 0'

@when('I run the sniff command using the loopback interface IP as source and a warts file as output')
def step_impl(context):
	result = subprocess.run(['sudo', context.scamper_path, '-O', 'warts', '-o', context.output_file_path,
							'-I', context.sniff_cmd], check=True, capture_output=True, text=True)
	context.stderr = result.stderr
	context.returncode = result.returncode
	context.ping_subproc.send_signal(signal.SIGINT)
	ping_out, ping_err = context.ping_subproc.communicate()
	assert len(ping_out) > 0, 'expected ping to return non empty output'
	assert len(ping_err) == 0, 'expected ping to return empty stderr'
	assert context.ping_subproc.returncode == 0, 'expected ping to return 0'

def get_loopback_interface_ip():
	interface_list = netifaces.interfaces()
	source_ip = ''
	for interface in interface_list:
		if interface != "lo":
			continue
		address_entries = netifaces.ifaddresses(interface)

		print(address_entries)
		for _, address_entry in address_entries.items():
			if address_entry[0]['addr'] == '00:00:00:00:00:00' or address_entry[0]['addr'] == '::1':
				continue
			source_ip = address_entry[0]['addr']
			break

	return source_ip
