
<br />
<div align="center">
  <a href="https://github.com/ITZIM4D/NoNMAP">
  </a>

<h3 align="center">NoNMAP</h3>

  <p align="center">
    A basic port scanner like NMAP written in python. 
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

To learn more about networking and cybersecurity I wanted to recreate NMAP in a basic way and then keep adding onto it. This project is my first step in doing that and I am hoping to create more projects like this in the future.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* Python
* Socket (Standard Library)
* sys (Standard Library)
* json (standard Library)

### Functionality Included

* Command-line argument parsing using `sys.argv`
* Reads target IP address from user input
* Loads common ports from `commonPorts.json`
* Scans TCP ports using Python sockets
* Uses timeout-based connection checks
* Identifies and prints open ports
* Iterates through a predefined list of common ports

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started


### Prerequisites

* Python 
Either use `brew install python` on Mac or go to [Python's Website](https://www.python.org/downloads/) and download it from there

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/ITZIM4D/NoNMAP.git
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

* Scan an IP 
``` bash
❯ python3 NoNMAP.py 127.0.0.1
Scanning common ports on 127.0.0.1
Port 3306 is open
Port 5432 is open
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>