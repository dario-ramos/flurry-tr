from behave import *


@given('I am running scamper from the command line')
def step_impl(context):
    # TODO Implement
    pass


@when('I run the "flurry-tr" scamper command with argument bbp = "3"')
def step_impl(context):
    # TODO Implement
    assert True is False


@then('I should see "3" back-to-back ping packages sent')
def step_impl(context):
    # TODO Implement
    assert context.failed is False


@when('I run the "flurry-tr" scamper command with argument bbp = "10"')
def step_impl(context):
    # TODO Implement
    assert True is False


@then('I should see an error message saying that bbp = "10" is too large')
def step_impl(context):
    # TODO Implement
    assert context.failed is False
