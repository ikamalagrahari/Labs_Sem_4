#Create a simulator object
set ns [new Simulator]
#Open the nam trace file
set nf [open dv.nam w]
$ns namtrace-all $nf
#Define a 'finish' procedure
 proc finish {} {
 global ns nf
 $ns flush-trace
 #Close the trace file
 close $nf
 #Executenam on the trace file
 exec nam dv.nam &
 exit 0
}
#Create six nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
#Create links between the nodes
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
$ns duplex-link $n4 $n5 1Mb 10ms DropTail
$ns duplex-link $n5 $n0 1Mb 10ms DropTail

#Create a TCP agent and attach it to node n1
set tcp [new Agent/TCP]
$tcp set class_ 1
$ns attach-agent $n1 $tcp
#Create a TCP Sink agent (a traffic sink) for TCP and attach it to node n3
set sink [new Agent/TCPSink]
$ns attach-agent $n5 $sink

#Connect the traffic sources with the traffic sink
$ns connect $tcp $sink

# Create a CBR traffic source and attach it to tcp0
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.01
$cbr attach-agent $tcp

$ns rtproto DV 

$ns rtmodel-at 1.0 down $n0 $n1 
$ns rtmodel-at 2.0 up $n0 $n1 

#Schedule events for the CBR agents
$ns at 0.5 "$cbr start"
$ns at 3.0 "$cbr stop"

#Call the finish procedure after 5 seconds of simulation time
$ns at 4.0 "finish"

#Run the simulation
$ns run

Output:
  

Program for 8 nodes ring topology

#Create a simulator object
set ns [new Simulator]
#Open the nam trace file
set nf [open dv2.nam w]
$ns namtrace-all $nf
#Define a 'finish' procedure
 proc finish {} {
 global ns nf
 $ns flush-trace
 #Close the trace file
 close $nf
 #Executenam on the trace file
 exec nam dv2.nam &
 exit 0
}

$ns color 1 Red
$ns color 2 Yellow

#Create six nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]

#Create links between the nodes
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
$ns duplex-link $n4 $n5 1Mb 10ms DropTail
$ns duplex-link $n5 $n6 1Mb 10ms DropTail
$ns duplex-link $n6 $n7 1Mb 10ms DropTail
$ns duplex-link $n7 $n0 1Mb 10ms DropTail

#Create a TCP agent and attach it to node n1
set tcp1 [new Agent/TCP]
set tcp2 [new Agent/TCP]
$tcp1 set class_ 1
$tcp2 set class_ 1
$ns attach-agent $n1 $tcp1
$ns attach-agent $n3 $tcp2
$tcp1 set fid_ 1
$tcp2 set fid_ 2
#Create a TCP Sink agent (a traffic sink) for TCP and attach it to node n3
set sink1 [new Agent/TCPSink]
set sink2 [new Agent/TCPSink]
$ns attach-agent $n5 $sink1
$ns attach-agent $n6 $sink2

#Connect the traffic sources with the traffic sink
$ns connect $tcp1 $sink1
$ns connect $tcp2 $sink2

# Create a CBR traffic source and attach it to tcp0
set cbr1 [new Application/Traffic/CBR]
set cbr2 [new Application/Traffic/CBR]
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.01
$cbr1 attach-agent $tcp1
$cbr2 set packetSize_ 500
$cbr2 set interval_ 0.01
$cbr2 attach-agent $tcp2
$ns rtproto DV 

$ns rtmodel-at 1.0 down $n0 $n1 
$ns rtmodel-at 2.0 up $n0 $n1 
$ns rtmodel-at 1.5 down $n3 $n4
$ns rtmodel-at 2.5 up $n3 $n4
#Schedule events for the CBR agents
$ns at 0.5 "$cbr1 start"
$ns at 3.0 "$cbr1 stop"
$ns at 1.0 "$cbr2 start"
$ns at 3.5 "$cbr2 stop"

#Call the finish procedure after 5 seconds of simulation time
$ns at 4.0 "finish"

#Run the simulation
$ns run


 
 