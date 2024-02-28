Feature: Trace command

   As a scamper user
   I want to run the pre-existing "trace" command
   So that I can verify it still works after adding the new traceb command
   
   Scenario: Default
      Given I am running scamper trace from the command line
      When I run the trace scamper command with just an IP address argument
      Then I should get a trace response without errors
