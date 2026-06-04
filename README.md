
<br />
<div align="center">
  <a href="https://github.com/ITZIM4D/NoNMAP">
  </a>

<h3 align="center">WebServer</h3>

  <p align="center">
    A multithreaded HTTP server using a fixed size thread pool to handle concurrent connections and tasks 
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



## About The Project

To increase my knowledge of threads and backend applications I want to make an HTTP server that I will continue to build off of.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* C++
* Docker

### Functionality Included

* 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started


### Prerequisites

* Docker
Either use `brew install Docker` on Mac or go to [Docker's Website](https://www.docker.com/products/docker-desktop/) and download it from there

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/ITZIM4D/HTTPWebServer.git
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Usage

* Build the docker image (include --no-cache for a clean build)
``` bash
❯ docker build --no-cache -t webserver . && docker run webserver
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>