from behave import *
import subprocess


@given('I am running scamper from the command line')
def step_impl(context):
    context.scamper_path = '../scamper/scamper'
    context.bairestr_cmd = 'traceb'
    context.bbp_flag = 'b'

@when('I run the traceb scamper command with just an IP address argument')
def step_impl(context):
	result = subprocess.run(['sudo', context.scamper_path, '-c', context.bairestr_cmd,
			'-i', '172.217.30.228'], check=True, capture_output=True, text=True)
	context.stdout = result.stdout
	context.stderr = result.stderr
	
@then(u'I should get the hard-coded response without errors')
def step_impl(context):
    assert(context.stdout == 'placeholder response from traceb\n')
    assert(context.stderr == '')

# TODO Re-enable these when BBP is implemented
# @when('I run the "traceb" scamper command with argument bbp = "3"')
#def step_impl(context):
#    result = subprocess.run([context.scamper_path, '-c', context.bairestr_cmd,
#                             context.bbp_flag, '3', '-i', '172.217.30.228'], check=True)
#    print(result)
#    assert True is False


# @then('I should see "3" back-to-back ping packages sent')
# def step_impl(context):
#    # TODO Implement
#    assert context.failed is False


# @when('I run the "bairestr" scamper command with argument bbp = "10"')
# def step_impl(context):
#    result = subprocess.run([context.scamper_path, '-c', context.bairestr_cmd,
#                             context.bbp_flag, '10', '-i', '172.217.30.228'], check=True)
#    print(result)
#    assert True is False


# @then('I should see an error message saying that bbp = "10" is too large')
# def step_impl(context):
#    # TODO Implement
#    assert context.failed is False

