# investigating std::variant overhead

A microbenchmark replicating some overhead I measured in an application
that leverages std::variant across library boundaries, thus preventing
inlining.

## results

Results on my machine with a Intel(R) Core(TM) i7-5600U CPU @ 2.60GHz,
compiled in RelWithDebInfo mode (i.e. `-O2 -g`):

### GCC 10.2.0 (slowdown of 720% or 838%)

`using Var0 = uint64_t` (Baseline / no std::variant):
```
 Performance counter stats for './variant 0' (5 runs):

            341,67 msec task-clock                #    0,998 CPUs utilized            ( +-  0,72% )
                11      context-switches          #    0,033 K/sec                    ( +- 30,59% )
                 1      cpu-migrations            #    0,004 K/sec                    ( +- 31,18% )
               382      page-faults               #    0,001 M/sec                    ( +-  0,16% )
     1.065.848.451      cycles                    #    3,120 GHz                      ( +-  0,36% )  (61,93%)
     2.102.158.173      instructions              #    1,97  insn per cycle           ( +-  0,05% )  (74,61%)
       656.675.208      branches                  # 1921,950 M/sec                    ( +-  0,14% )  (74,79%)
            37.706      branch-misses             #    0,01% of all branches          ( +-  1,51% )  (75,27%)
       524.873.150      L1-dcache-loads           # 1536,193 M/sec                    ( +-  0,07% )  (75,43%)
        16.486.841      L1-dcache-load-misses     #    3,14% of all L1-dcache accesses  ( +-  0,02% )  (75,43%)
            68.399      LLC-loads                 #    0,200 M/sec                    ( +- 11,18% )  (49,78%)
             4.058      LLC-load-misses           #    5,93% of all LL-cache accesses  ( +- 61,06% )  (49,30%)

           0,34247 +- 0,00257 seconds time elapsed  ( +-  0,75% )
```

`using Var1 = std::variant<uint64_t>`:
```
 Performance counter stats for './variant 1' (5 runs):

          2.491,14 msec task-clock                #    0,999 CPUs utilized            ( +-  0,10% )
                38      context-switches          #    0,015 K/sec                    ( +- 40,81% )
                 4      cpu-migrations            #    0,001 K/sec                    ( +- 16,67% )
               383      page-faults               #    0,154 K/sec                    ( +-  0,30% )
     7.773.391.551      cycles                    #    3,120 GHz                      ( +-  0,03% )  (62,42%)
     4.073.914.612      instructions              #    0,52  insn per cycle           ( +-  0,00% )  (74,97%)
       657.336.683      branches                  #  263,870 M/sec                    ( +-  0,01% )  (74,97%)
            84.887      branch-misses             #    0,01% of all branches          ( +-  3,03% )  (74,97%)
     1.706.806.939      L1-dcache-loads           #  685,152 M/sec                    ( +-  0,01% )  (75,03%)
        16.709.392      L1-dcache-load-misses     #    0,98% of all L1-dcache accesses  ( +-  0,03% )  (75,10%)
           158.525      LLC-loads                 #    0,064 M/sec                    ( +-  3,40% )  (50,00%)
            17.597      LLC-load-misses           #   11,10% of all LL-cache accesses  ( +-  9,53% )  (49,93%)

           2,49302 +- 0,00260 seconds time elapsed  ( +-  0,10% )
```

`using Var2 = std::variant<uint64_t, uint32_t>`:
```
 Performance counter stats for './variant 2' (5 runs):

          2.865,06 msec task-clock                #    0,998 CPUs utilized            ( +-  0,16% )
               280      context-switches          #    0,098 K/sec                    ( +- 60,75% )
                14      cpu-migrations            #    0,005 K/sec                    ( +- 27,83% )
               381      page-faults               #    0,133 K/sec                    ( +-  0,13% )
     8.958.269.283      cycles                    #    3,127 GHz                      ( +-  0,03% )  (62,39%)
     7.221.058.673      instructions              #    0,81  insn per cycle           ( +-  0,02% )  (74,93%)
     1.051.224.728      branches                  #  366,912 M/sec                    ( +-  0,03% )  (74,97%)
           117.336      branch-misses             #    0,01% of all branches          ( +- 15,68% )  (75,04%)
     2.887.449.354      L1-dcache-loads           # 1007,816 M/sec                    ( +-  0,01% )  (75,01%)
        16.833.544      L1-dcache-load-misses     #    0,58% of all L1-dcache accesses  ( +-  0,39% )  (75,03%)
           231.853      LLC-loads                 #    0,081 M/sec                    ( +- 15,34% )  (50,02%)
            29.185      LLC-load-misses           #   12,59% of all LL-cache accesses  ( +- 18,40% )  (49,93%)

           2,87072 +- 0,00276 seconds time elapsed  ( +-  0,10% )
```

### clang 11.1.0 (slowdown of 14% or 84%)

`using Var0 = uint64_t` (Baseline / no std::variant):
```
 Performance counter stats for './variant 0' (5 runs):

            346,50 msec task-clock                #    0,997 CPUs utilized            ( +-  1,38% )
                34      context-switches          #    0,097 K/sec                    ( +- 48,58% )
                 1      cpu-migrations            #    0,002 K/sec                    ( +- 66,67% )
               382      page-faults               #    0,001 M/sec                    ( +-  0,24% )
     1.079.167.246      cycles                    #    3,114 GHz                      ( +-  0,77% )  (62,33%)
     2.103.531.907      instructions              #    1,95  insn per cycle           ( +-  0,11% )  (74,99%)
       657.171.926      branches                  # 1896,579 M/sec                    ( +-  0,09% )  (74,95%)
            42.756      branch-misses             #    0,01% of all branches          ( +-  3,25% )  (74,95%)
       524.893.755      L1-dcache-loads           # 1514,828 M/sec                    ( +-  0,06% )  (75,15%)
        16.497.132      L1-dcache-load-misses     #    3,14% of all L1-dcache accesses  ( +-  0,12% )  (75,31%)
            47.037      LLC-loads                 #    0,136 M/sec                    ( +-  8,09% )  (49,90%)
             7.534      LLC-load-misses           #   16,02% of all LL-cache accesses  ( +- 35,78% )  (49,73%)

           0,34770 +- 0,00450 seconds time elapsed  ( +-  1,29% )
```


`using Var1 = std::variant<uint64_t>`:
```
 Performance counter stats for './variant 1' (5 runs):

            395,06 msec task-clock                #    0,991 CPUs utilized            ( +-  0,50% )
                58      context-switches          #    0,146 K/sec                    ( +- 25,40% )
                 3      cpu-migrations            #    0,007 K/sec                    ( +- 13,36% )
               382      page-faults               #    0,966 K/sec                    ( +-  0,18% )
     1.237.260.633      cycles                    #    3,132 GHz                      ( +-  0,28% )  (61,76%)
     2.891.221.196      instructions              #    2,34  insn per cycle           ( +-  0,12% )  (74,58%)
       657.485.185      branches                  # 1664,250 M/sec                    ( +-  0,07% )  (74,90%)
            45.695      branch-misses             #    0,01% of all branches          ( +-  5,31% )  (75,02%)
       525.225.462      L1-dcache-loads           # 1329,469 M/sec                    ( +-  0,08% )  (75,13%)
        16.500.768      L1-dcache-load-misses     #    3,14% of all L1-dcache accesses  ( +-  0,05% )  (75,59%)
            57.421      LLC-loads                 #    0,145 M/sec                    ( +-  9,26% )  (49,96%)
             9.089      LLC-load-misses           #   15,83% of all LL-cache accesses  ( +- 30,70% )  (49,38%)

           0,39866 +- 0,00262 seconds time elapsed  ( +-  0,66% )
```

`using Var2 = std::variant<uint64_t, uint32_t>`:
```
 Performance counter stats for './variant 2' (5 runs):

            638,65 msec task-clock                #    0,996 CPUs utilized            ( +-  0,85% )
                45      context-switches          #    0,071 K/sec                    ( +- 63,14% )
                 4      cpu-migrations            #    0,006 K/sec                    ( +- 69,82% )
               382      page-faults               #    0,598 K/sec                    ( +-  0,13% )
     1.998.567.369      cycles                    #    3,129 GHz                      ( +-  0,51% )  (62,16%)
     6.297.649.870      instructions              #    3,15  insn per cycle           ( +-  0,05% )  (74,82%)
     1.050.921.005      branches                  # 1645,530 M/sec                    ( +-  0,05% )  (75,07%)
            49.234      branch-misses             #    0,00% of all branches          ( +- 11,14% )  (75,28%)
     1.442.218.800      L1-dcache-loads           # 2258,223 M/sec                    ( +-  0,04% )  (75,28%)
        16.537.896      L1-dcache-load-misses     #    1,15% of all L1-dcache accesses  ( +-  0,10% )  (75,27%)
            79.831      LLC-loads                 #    0,125 M/sec                    ( +-  8,38% )  (49,65%)
             8.658      LLC-load-misses           #   10,84% of all LL-cache accesses  ( +- 52,74% )  (49,45%)

           0,64147 +- 0,00657 seconds time elapsed  ( +-  1,02% )
```
