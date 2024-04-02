
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

The performance of the two kernels was tested on the DAXPY Function with different vector sizes:

- 2^20 (or 1048576)
- 2^24 (or 16777216)
- 2^27 (or 134217728)

## Demo/ Analysis / Comparison

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
            <td>x</td>
            <td>o</td>
            <td>x</td>
            <td>o</td>
            <td>x</td>
            <td>o</td>
        </tr>
        <tr>
            <td>Release Mode</td>
            <td>x</td>
            <td>o</td>
            <td>x</td>
            <td>0</td>
            <td>x</td>
            <td>0</td>
        </tr>
    </tbody>
</table>

Lorem Ipsum





