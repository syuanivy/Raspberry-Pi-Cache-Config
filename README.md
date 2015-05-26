For more information please go to [**wiki**](https://github.com/rr118/CS631_Project03/wiki)

## Goal 


1. Performance analysis of program running on different medium.
2. Detection of Raspberry PI CPU L1 Cache configuration.


### Performance analysis

Increment 10MB integer array from 0 to N:

### prog1, cache friendly/efficient
| Bare Metal        | Raspbian           | Qemu on Raspbian  |
|:------------- |:-------------:|:-----:|
| 1746 ms      | 159 ms | 846 ms |
  N = 1000


### prog2, cache unfriendly/inefficient

| Bare Metal        | Raspbian           | Qemu on Raspbian  |
|:------------- |:-------------:|:-----:|
|  1797 ms      | 614 ms |1061 ms |
   N = 1000

### visualization

![n 1000](https://cloud.githubusercontent.com/assets/8441306/7372560/45651ebe-ed7c-11e4-8879-de587f98c01d.png)

Block size: 32 bytes

![rp_block_macro](https://cloud.githubusercontent.com/assets/8441306/7224120/c599efa6-e6e2-11e4-9df8-ecbb7f4b3cac.png)

Data cache size: 16kb

![capacity](https://cloud.githubusercontent.com/assets/8441306/7363841/44f0b030-ed34-11e4-9499-78a760e88f68.png)


 
## L1 Cache Configuration

| Block Size       | Cache Size |  Number of Ways   |    
|:------------- |:-------------:|:-----:|
| 8 words     | 16 KB      | 4 |

## Discussion
1. __Bare metal is running almost 10 times slower than Raspbian.__
   After some digging on the technical documents and some messing around, the L1 cache is not originally enabled.
   We can use the coprocessor instruction to read or manipulate cache behaviours, but it could be another project.

2. __QEMU bare metal is running faster than pure bare metal.__
   A guess would be that since QEMU is running on an environment where caches are enabled, it basically exploit the hardware
   performance even better than the pure bare metal.

3. __QEMU bare metal is running slower than Raspbian__
   This is expected, since there are overhead on emulation.

4. __Prog1 and Prog2 are equally slow on bare metal (0.02 times slower).__
   This is consistent with the notion that L1 cache is not enabled on bare metal.

5. __Other caching mechanisms.__
   Prog2 on Raspbian is not as slow as Prog1 on bare metal (2.85 times slower), indicating other caching mechanisms might be    involved on Raspbian, i.e. L2 cache.

   Short array assay on Raspbian and bare metal    
![vs](https://cloud.githubusercontent.com/assets/8441306/7363419/f694a068-ed2e-11e4-9494-ec8ece9e8f49.png)


6. __Increasing the interval of access along the arrays can further slow down Prog2 for unclear reason (data not shown).__
  Associativity may be involved? 

![slower](https://cloud.githubusercontent.com/assets/8441306/7376134/9162d48a-ed92-11e4-9dc9-9899ce6e22b3.png)


# Raspberry-Pi-Cache-Config
