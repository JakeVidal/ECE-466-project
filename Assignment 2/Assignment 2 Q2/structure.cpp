#include "systemc.h"
#include "fifo.h"
#include "producer.h"
#include "consumer.h"
#include <iostream>
#include <iomanip>

using namespace std;

int sc_main(int argc, char* argv[]){
    sc_clock fastClk("fastClk", 5, SC_NS, 0.5, 1, SC_NS);
    sc_clock slowClk("slowClk", 10, SC_NS, 0.5, 1, SC_NS);

    fifo<int, 8> FF("fifo");

    producer<int> PROD("producer");
    PROD.clk(fastClk); PROD.out(FF);

    consumer<int> CON("consumer");
    CON.clk(slowClk); CON.in(FF);

    sc_start(210, SC_NS);
    return 0;
};