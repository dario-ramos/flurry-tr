from behave import *
import subprocess
import re
from public_ips import get_public_ip

@given('I am running scamper tracelb from the command line')
def step_impl(context):
	context.scamper_path = '../scamper/scamper'
	context.tracelb_cmd = 'tracelb'
	context.public_ip = get_public_ip()
	print(f'\tselected public IP: {context.public_ip}\n')

@when('I run the tracelb scamper command with just an IP address argument')
def step_impl(context):
	result = subprocess.run(['sudo', context.scamper_path, '-c', context.tracelb_cmd,
			'-i', context.public_ip], check=True, capture_output=True, text=True)
	context.stdout = result.stdout
	context.stderr = result.stderr
	context.returncode = result.returncode

@then(u'I should get a non-empty tracelb response without errors')
def step_impl(context):
	assert context.stderr == '', 'expected empty stderr'
	assert context.returncode == 0, 'expected return code 0'
	assert len(context.stdout) != 0, 'expected non-empty output'
