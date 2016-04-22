#!/bin/bash
# this is needed to keep the container running in jenkins 
# so that the container can be created and the build process
# can attach to it
# simply running the container with docker run -it <name> 
# does not work out because this results in this error:
# cannot enable tty mode on non tty input
# when trying to run from jenkins
sleep 1000000000000000
