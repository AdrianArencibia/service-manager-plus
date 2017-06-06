# Service Manager Plus
Service Manager Plus will help you make your service management easier. You can start, stop and restart multiple services at the same time. You can also rename services and add them to a list of favorites.

![Service Manager Plus](img/output.gif)
## USAGE: sm OPTION ARG
    OPTION:
         For list (not need ARG):
             l: show all services.
             lr: show all running services.
             lr: show all stoped services.
         For actions: ARG can be the services names or key from Favorites.
             [1|s]: to start services(ARG).
             [0|st]: to stop services(ARG).
             [-1|r]: to restart services(ARG).
             i: to get information about services(ARG).
         For favorites:
             f: to list the favorite services.
             fa: add service to favorites. ARG [name key]
                 Example: fa cntlm c
             fr: modify key of a service in favorites. ARG [key newkey]
                 Example: fr c cnt
             fd: delete service from favorites. ARG [key]
                 Example: fd cnt
