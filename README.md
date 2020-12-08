# 471-HTTP-Server
Final Project for CMPT 471

Environment:
This project was compiled and runs on Ubuntu 18.04.4 LTS (64-bit)

Build and run:
Enter the command `make` to build our project, followed by `./http_server` to run it

Test cases:
With the program running, open your browser and navigate to `http://localhost:9090/index.html`. This should deliver a page called "Test Page" with the text "You have arrived at the webpage."

Next, go to `http://localhost:9090/courses.html`. This should delived a page listing a few CMPT courses offered at SFU.

Next, go to `http://localhost:9090/nothere.html` (or any html file not in the folder). You should get a page saying "404 Not Found."

There are no known bugs at this time.
