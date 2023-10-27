from behave import *
import subprocess
import os
import re
import public_ips

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
