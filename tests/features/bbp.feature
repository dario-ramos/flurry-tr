Feature: Back-to-back packets (BBP)

   As a scamper user
   I want to run the new "bairestr" command specifying BBP
   So that I can perform different measurements

   Scenario: Valid BBP
      Given I am running scamper from the command line
      When I run the "bairestr" scamper command with argument bbp = "3"
      Then I should see "3" back-to-back ping packages sent

   Scenario: Invalid BBP
      Given I am running scamper from the command line
      When I run the "bairestr" scamper command with argument bbp = "10"
      Then I should see an error message saying that bbp = "10" is too large
