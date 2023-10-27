Feature: Other commands

   As a scamper user
   I want to make sure all commands work at a basic level
   So that I can ensure they are not broken by changes

   Scenario: dealias
      Given I am running scamper dealias from the command line using -I
      When I run the dealias scamper command in a basic usage scenario
      Then I should get a non-empty dealias response without errors

   Scenario Outline: commands invoked via -I that output a warts file
      Given I am running <scamper_command_name> from the command line using -I
      When I invoke it with the -I flag set to: <scamper_command_i_flag>
      Then I should get a non-empty output file and exit code should be zero

      Examples:
         |scamper_command_name  |scamper_command_i_flag              |
         |host                  |host google.com                     |
         |neighbourdisc         |neighbourdisc -i lo 192.168.20.215  |

   Scenario Outline: commands invoked via -c and -i
      Given I am running <scamper_command> from the command line using -c
      When I run the command with an IP address obtained via <ip_selector>
      Then I should get a non-empty response without errors

      Examples:
         |scamper_command  |ip_selector               |
         |tracelb          |get_public_ip_restricted  |
         |ping             |get_public_ip             |
         |sting            |get_public_ip             |
         |tbit             |get_public_ip             |
