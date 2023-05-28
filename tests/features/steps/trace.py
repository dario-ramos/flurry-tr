from behave import *
import subprocess
import re
from public_ips import get_public_ip

@given('I am running scamper trace from the command line')
def step_impl(context):
	context.scamper_path = '../scamper/scamper'
	context.trace_cmd = 'trace'
	context.public_ip = get_public_ip()
	print(f'\tselected public IP: {context.public_ip}\n')

@when('I run the trace scamper command with just an IP address argument')
def step_impl(context):
	result = subprocess.run(['sudo', context.scamper_path, '-c', context.trace_cmd,
			'-i', context.public_ip], check=True, capture_output=True, text=True)
	context.stdout = result.stdout
	context.stderr = result.stderr

@then(u'I should get a trace response without errors')
def step_impl(context):
	assert context.stderr == '', 'expected empty stderr'

	trace_response = context.stdout
	assert trace_response != '', 'expected non empty trace response'
	response_lines = trace_response.split('\n')
	assert len(response_lines) > 1, 'expected at least two lines in response'
	assert re.fullmatch("traceroute from \d+\.\d+\.\d+\.\d+ to \d+\.\d+\.\d+\.\d+", response_lines[0]), \
		f'invalid trace response: expected first line to be of the form "traceroute from <IP_src> to <IP>_dst"'

	for i in range(1, len(response_lines)-1):
		if re.fullmatch('^\s*\d+\s+\d+\.\d+\.\d+\.\d+\s+\d+\.\d+\s+ms$', response_lines[i]):
			continue
		assert re.fullmatch('^\s*\d+\s*\*$', response_lines[i]), \
			f'invalid trace response: expected line {i} to be of the form: " {i} <IP_hop> <time> ms" or "{i} *", got {response_lines[i]}'
