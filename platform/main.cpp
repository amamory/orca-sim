#include <Event.h>
#include <Simulator.h>

#include <HFRiscvModel.h>
#include <MemoryModel.h>
#include <DmniModel.h>
#include <NocRouterModel.h>

#define CYCLES_TO_SIM 100000

#define MEM_SIZE  0x00100000
#define SRAM_BASE 0x40000000

//memory map
#define DMNI_CONF 0xFF000010
#define DMNI_INTR 0xFF000000

int main(int argc, char** argv){

	if(argc < 2){
		std::cout << "Usage: teste <app>.bin" << endl;
		exit(0);
	}
	
	cout << "Simulation stated" << endl;
	
	//creates a new simulator
	Simulator s = Simulator(CYCLES_TO_SIM);

	//creates a new memory
	MemoryModel mem1 = MemoryModel(
		"mem1",   //instance name 
		MEM_SIZE, //total memory size (in words) 
		true ,    //wipe memory at statup
		std::string(argv[1])  //load a program into memory
	);

	//creates a new processor
	HFRiscvModel hfr1 = HFRiscvModel(
		"hf001",          //instance name
		mem1.GetMemPtr(), //pointer to memory TODO: fix API for using [] override
		MEM_SIZE,         //total size (in words)
		SRAM_BASE         //pc starting location
	);

	//creates a dmni and attaches to the router module
	DmniModel dmni1 = DmniModel("dmni1");

    //reset all hardware
    hfr1.Reset();
    dmni1.Reset();
    mem1.Reset();
    
    hfr1.PortMap(
        dmni1.GetIntr(), //intr_in
        0, //mem_data_read
        0  //mem_pause
    );
    
    dmni1.PortMap(
        0, //set_address
        0, //set_address_2
        0, //set_size
        0, //set_size_2
        0, //set_op
        0, //start
        0, //config_data
        0, //mem_data_read
        0, //credit_i
        0, //rx
        0  //data_in
    );

    //mem1.PortMap();

    //s.Schedule(Event(0, &mem1));
	s.Schedule(Event(0, &dmni1));
	s.Schedule(Event(0, &hfr1));
    s.Schedule(Event(0, &mem1));

	s.Run();

	cout << "\nSimulation ended" << endl;
	
	//dump mem on screen		
	mem1.Dump(0, MEM_SIZE);
}
