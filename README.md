# baires-scp

This is essentially a fork of Scamper's cvs-20210324 release from March 2021. Scamper is not on Github, so I basically copied their source ball
and started editing. 

The main goal of this fork is to add a new command to Scamper: Baires traceroute. This command sends probe packets back to back, without 
waiting for a response to send the next one.

 Secondary goals:
 
 * Add automated acceptance tests, initially covering the new command only.
 * Add unit tests for all the new functions, and modified pre-existing ones.
 * Implement design by contract to ensure quality for all new functions and modified pre-existing ones.
 * Add continuous integration.
 
 These goals are intended to ensure quality for the new command, while opening the door for adding that to the remaining commands.
