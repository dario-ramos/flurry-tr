Feature: Other commands

   As a scamper user
   I want to make sure all commands work at a basic level
   So that I can ensure they are not broken by changes
   
   Scenario: tracelb
      Given I am running scamper tracelb from the command line
      When I run the tracelb scamper command with just an IP address argument
      Then I should get a non-empty tracelb response without errors