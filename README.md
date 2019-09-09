# Micro (&#181;) Rapid-Simulation API -- URSA

URSA is a lightweigth API for the rapid simulation of computing systems. The goal of the project is to provide an alternative to the cubersome, expensive, and buggy on-the-shelf tools. Advantages of URSA over other simulations may include (i) easy-to-use API, with just a few classes and methods, (ii) no dependecies on software other than c++ standard library, (iii) near-cycle accuracy regardless of system size, and (iv) standalone simulation engine that could be easily integrated within complex systems, e.g. batch servers.

## How does URSA work?

URSA implements discrete-event simulation along with abstract modeling of hardware modules. When combined, these approaches permit URSA to simulate hardware platforms faster than typical RTL tools. Depending on the complexity of simulated systems, URSA can even surpass the execution speed of the real hardware. Such a feature may come in hand when debugging software for non-standard platforms, mainly when developing basic software such as peripheral drivers.

In URSA, hardware models are described in C++, using classes and some other abstractions. As in other tools, testbenchs can be created to hardware models, and different configurations of platforms can be simulated. The trade-off between simulation performance and accuracy if treated in models, so a same hardware pieca may have different models that be used within different simulators. 

The picture below illustrates the many parts involved in a typical simulation process.

![Components of URSA and their interaction.](https://raw.githubusercontent.com/andersondomingues/ursa/stable/docs/URSA.png?raw=true)

## What assets does URSA provide?

* A static library containing primitives for modeling hardware using C++ classes;
* A base simulator class based on discrete-event simulation strategy;
* Base models for signals, memories and buffers.

## Project Status and Roadmap

- We have succefully simulated a fully-functional MPSoC platform comprising a mesh-based NoC architecture interconnecting up to 16x16 processing elements (256 cores). More information on the platform can be found at ![ORCA Project's Repository.](https://github.com/andersondomingues/orca-mpsoc).

- Current efforts are directed to increase simulation time, reduce models' complexity, and provide productivity tools. 
 
- Develop benchmarks, so that we can accurately measure the performance of simulators made with URSA

- Study other models to speed-up the simulation such as virtualization techniques.

- Develop debugging and visualization tools·

## Getting Started

*Content in this section is outdated and will be promptly replaced.*

- A very short tutorial is included in ``docs/URSA_Sulphane - The Lazy Manual``. 

### Project organisation 

*NOTE: Current files correpond to both URSA and ORCA projects. We are currently working on striping these projects from each other. In meanwhile, please refer to ``simulator`` and ``models`` folders.

- ``/bin`` : compiled binaries and external libraries
- ``/docs`` : contains a tutorial and images used in this MD file, also serving as output folder for doxygen
- ``/logs`` : output from the hardware models, as well as other implementation-specific outputs and debugging
- ``/models`` : general purpose hardware models (independent modules)
- ``/platforms`` : platform-specific hardware models (top-level modules)
- ``/simulator`` : URSA's core
- ``/software`` : software to be deployed to emulated platforms
- ``/tools`` : several scripts and helpers

- ``Configuration.mk`` : several configurations related to the simulator and simulated platforms.
- ``Makefile`` : type `$make clean all` to compile and test

## Generating API Documentation

- Make sure you have installed ``doxygen`` installed in your system. Go to the root directory of URSA (``ursa``) and type ``$make documentation``. Documentation will be deployed to ``docs/doxygen`` folder. You can access docs by opening ``docs/doxygen/html/index.html`` in any web browser (e.g., ``firefox``). LaTeX documentation can be generate by  typeing ``make -C docs/doxygen/latex/``. The output file ``docs/doxygen/latex/refman.pdf`` contains the generated documentation. 

## Third-Party Work

- HF-RISCV and HELLFIREOS. The hf-riscv core is maintained by Sergio Johann (sjohann81). More information on his work can be found at [his repository](https://github.com/sjohann81). Provided Riscv32im model is based on his work. Besides, we use [sjohann81's HellfireOS operating system](https://github.com/sjohann81) within the processing tiles of the ORCA platform. 

- HEMPS (and HERMES). The GAPH group maintains the HEMPS project. More information on their work can be found at [their website](http://www.inf.pucrs.br/hemps/getting_started.html). Provided network-on-chip router model is based on the RTL models available at [their repository](https://github.com/GaphGroup/hemps). 

## Licensing

This project is licensed under GNU Affero General Public License version 3. See ``LICENSE.MD`` for more information. 

## Contact

For now, I ([andersondomingues](https://github.com/andersondomingues)) am the only contributor to this project. Feel free to [mail me](mailto:ti.andersondomingues@gmail.com).



