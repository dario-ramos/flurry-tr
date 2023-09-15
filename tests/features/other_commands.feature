Feature: Other commands

   As a scamper user
   I want to make sure all commands work at a basic level
   So that I can ensure they are not broken by changes

   Scenario: dealias
      Given I am running scamper dealias from the command line using -I
      When I run the dealias scamper command in a basic usage scenario
      Then I should get a non-empty dealias response without errors

   Scenario: host
      Given I am running scamper host from the command line using -I
      When I run the host scamper command requesting a warts file as the output
      Then I should get a non-empty output file and exit code should be zero

   Scenario: neighbourdisc
      Given I am running scamper neighbourdisc from the command line using -I
      When I run the neighbourdisc scamper command requesting a warts file as the output
      Then I should get a non-empty output file and exit code should be zero

   Scenario Outline: commands invoked via -c and -i
      Given I am running <scamper_command> from the command line using -c
      When I run the command with an IP address argument
      Then I should get a non-empty response without errors

      Examples:
         |scamper_command  |
         |tracelb          |
         |ping             |
         |sting            |
         |tbit             |
