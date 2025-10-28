
// User allocates buffer
// keeps reference to it throughout execution
// Note the qalloc() utility function for allocating quantum memory (AcceleratorBuffer).
auto buffer = xacc::qalloc(3);
// Execute some circuit / composite instruction this writes result data to the buffer
accelerator->execute(buffer, circuit);
// User still has that buffer, get results
auto results = buffer->getMeasurementCounts();

// Can add/get metadata, measurements, and expectation values
std::vector<double> fidelities =buffer->getInformation("1q-gate-fidelities").as<std::vector<double>>();
auto counts = buffer->getMeasurementCounts();
auto expVal = buffer->getExpectationValueZ();
-----------------------------------------------------
auto qpu = xacc::getAccelerator("ibm:back-end");
auto quil = xacc::getCompiler("quil");
auto ir = quil->compile(R"(
__qpu__ ansatz(AcceleratorBuffer q, double x)
{
X 0
Ry(x) 1
CX 1 0
}
__qpu__ X0X1(AcceleratorBuffer q, double x)
{
ansatz(q, x);
H 0
H 1
MEASURE 0 [0]
MEASURE 1 [1]
}
)", qpu);
auto x0x1 = ir->getComposite("X0X1");
// Translate quil kernel to openqasm...
// It is just a joke to show XACC Compilers expose IR translation capabilities that enable this, 
// thereby providing quantum source-to-source translation (for instance, mapping Quil to OpenQasm).
auto openqasm = xacc::getCompiler("openqasm");
auto oqasmSrc = openqasm->translate(x0x1);
-------------------------------------------------------------------

  // Observable from string
auto x0x1 = xacc::getObservable("pauli");
x0x1->fromString("X0 X1");
// Measure, adds hadamards on 0,1
// and measure instructions
auto measured_circuit =
x0x1->observe(circuit)[0];
// Observable from options
auto h2 = xacc::getObservable("chemistry");
h2->fromOptions({
{"basis", "sto-3g"},
{"geometry", R"(
2
H 0.0 0.0 0.0
H 0.0 0.0 0.75
)"
}});






--------------hybrid quantum classical Algorithm-------------------

#include "xacc.hpp"
int main(int argc, char **argv) {
xacc::Initialize(argc, argv);
// Get the desired Accelerator and Optimizer
auto qpu =
xacc::getAccelerator("ibm:ibmq_valencia");
auto optimizer = xacc::getOptimizer("nlopt");
// Create the N=3 deuteron Hamiltonian
auto H_N_3 = xacc::quantum::getObservable(
"pauli",
std::string("15.531709 - 2.1433 X0X1 - "
"2.1433 Y0Y1 + .21829 Z0 - 6.125 Z1 - "
"9.625 Z2 - 3.91 X1 X2 - 3.91 Y1 Y2"));
// JIT map Quil QASM Ansatz to IR
xacc::qasm(R"(
.compiler xasm
.circuit ansatz
.parameters t0, t1
.qbit q
X(q[0]);
exp_i_theta(q, t0,
{{"pauli", "X0 Y1 - Y0 X1"}});
exp_i_theta(q, t1,
{{"pauli", "X0 Z1 Y2 - X2 Z1 Y0"}});
)");
auto ansatz = xacc::getCompiled("ansatz");
// Get the VQE Algorithm and initialize it
auto vqe = xacc::getAlgorithm("vqe");
vqe->initialize({
std::make_pair("ansatz", ansatz),
std::make_pair("observable", H_N_3),
std::make_pair("accelerator", qpu),
std::make_pair("optimizer", optimizer)
});
// Allocate some qubits and execute
auto buffer = xacc::qalloc(3);
vqe->execute(buffer);
// Get the result
auto energy =
(*buffer)["opt-val"].as<double>();
xacc::Finalize();
return 0;
}
--------------------------------------
  // Note Accelerators can be initialized
// with a HeterogeneousMap.
auto ibm = xacc::getAccelerator("ibm",
{{"shots", 8192},
{"backend", "ibmq_poughkeepsie"}});
ibm->execute(buffer, circuits);


  
