
# DAXPY Kernel x86-64 and C Implementation & Performance Comparison | LBYARCH - S15
## Authors
- [@luii-hub](https://github.com/luii-hub) 
- [@zhoeaeris](https://github.com/zhoexaeris)

## DAXPY Function implemented on a C Kernel and x86-64 Assembly Kernel was tested in both Debug Mode and Release Mode across different sizes of input vectors.
### Debug Mode Screenshots
![Vector Size: 2-20](screenshots/2^20_debug.png)
![Vector Size: 2-20](screenshots/2^24_debug.png)
![Vector Size: 2-20](screenshots/2^27_debug.png)

### Release Mode Screenshots
![Vector Size: 2-20](screenshots/2^20_release.png)
![Vector Size: 2-20](screenshots/2^24_release.png)
![Vector Size: 2-20](screenshots/2^27_release.png)

## Demo/ Analysis / Comparison
The performance of the two kernels was tested on the DAXPY Function with different vector sizes:
- 2^20 (or 1048576)
- 2^24 (or 16777216)
- 2^27 (or 134217728)

<table>
    <thead>
        <tr>
            <td>n (Size of X)</td>
            <td colspan=2 style="text-align: center;">2^20 (1,048,576)</td>
            <td colspan=2 style="text-align: center;">2^24 (16,777,216)</td>
            <td colspan=2 style="text-align: center;">2^27 (134,217,728)</td>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>Kernel</td>
            <td style="text-align: center;">C</td>
            <td style="text-align: center;">ASM</td>
            <td style="text-align: center;">C</td>
            <td style="text-align: center;">ASM</td>
            <td style="text-align: center;">C</td>
            <td style="text-align: center;">ASM</td>
        </tr>
        <tr>
            <td>Debug Mode</td>
            <td>0.005488427</td>
            <td>0.002741210</td>
            <td>0.084172490</td>
            <td>0.043751963</td>
            <td>0.687030793</td>
            <td>0.349576390</td>
        </tr>
        <tr>
            <td>Release Mode</td>
            <td>0.003314133</td>
            <td>0.003064247</td>
            <td>0.043285167</td>
            <td>0.043944323</td>
            <td>0.405919103</td>
            <td>0.498659870</td>
        </tr>
    </tbody>
</table>

Based on the results, it suggest that assembly implementation provides  better performance compared to the C implementation for the DAXPY kernel, especially when compiled with optimizations enabled (Release Mode). This is because of the low-level control and optimized instruction sequences facilitated in x86-64 programming. On the other hand, the release configuation showed a noticeable improvement in the performance for both C and x86-64 implementations, which is expected because this setting enables compiler optimizations. Lastly, for the overall scaling performance of the vector size, it can be seen that as the vector size increases, the execution time also increases for both implementations. However, the assembly implementation consistently maintains its performance advantage over the C implementation across all vector sizes.





