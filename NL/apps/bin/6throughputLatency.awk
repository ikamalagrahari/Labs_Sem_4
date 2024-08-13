BEGIN {
ftime = 0
stime = 0 flag=0 fsize=0 th=0 latency=0
}
{
if($1=="r"&&$4==3)
{
fsize+=$6 if(flag==0)
{
stime=$2 flag=1
}
ftime=$2
}
} 

END{
latency=ftime-stime th=(fsize*8)/latency
printf("\n Latency: %f",latency) printf("\n Throughput: %f",th)
}
