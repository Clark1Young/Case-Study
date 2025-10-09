# Case-Study

 Although QC has certain advantages over classical computing in specific scenarios,it does not sup-
port general computation well.Therefore,a general way to exploit QC is to treat quantum process-
ing units (QPUs) as additional, complex accelerators that are utilized for certain computing tasks.

Thus, a hybrid high performance computing will be discussed in this project.

When considering the hardware interface between the HPC host system and the quantum accelerators, many
strategies are possible, including 
1. remote access; As the name suggests, in a remote integration, the quantum accelerator is physically distant from the HPC host. In this scenario,
  quantum computers could be hosted and maintained by the quantum hardware provider, which significantly lowers the adoption barrier. It also allows the
  supercomputer to gain remote access to several different quantum computing technologies at a lower cost, which can be beneficial to some project.However,
  data security and integrity provided by a third party as well as by the network connection could be critical problem for some users.
2.  on-premises (or co-located) integration,
3.  on-node integration,
as depicted in Figure 3. Each of these brings distinct advantages and disadvantages and will suit different needs.
 
reference :
