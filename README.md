# EntropyAssessment

Cryptographic random bit generators (RBGs), also known as random number generators (RNGs), require a noise source that produces digital outputs with some level of unpredictability, expressed as min-entropy. [SP 800-90B](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90B.pdf) provides a standardized means of estimating the quality of a source of entropy.

## Disclaimer

NIST-developed software is provided by NIST as a public service. You may use, copy and distribute copies of the software in any medium, provided that you keep intact this entire notice. You may improve, modify and create derivative works of the software or any portion of the software, and you may distribute such modifications or works. Modified works should carry a notice stating that you changed the software and should note the date and nature of any such change. Please explicitly acknowledge the National Institute of Standards and Technology as the source of the software.

## Issues

Issues on this repository are strictly for problems or questions concerning the codebase as a standalone implementation of SP800-90B. Any questions or comments on the specification itself should be directed towards the authors of the document. 

## Requirements

This code package requires a C++11 compiler. The code uses OpenMP directives, so compiler support for OpenMP is expected. GCC is preferred (and the only platform tested). There is one method that involves a GCC built-in function (`chi_square_tests.h -> binary_goodness_of_fit() -> __builtin_popcount()`). To run this you will need some compiler that supplies this GCC built-in function (GCC and clang both do so).

The resulting binary is linked with bzlib, divsufsort, GMP MP and GNU MPFR, so these libraries (and their associated include files) must be installed and accessible to the compiler.

See [the wiki](https://github.com/usnistgov/SP800-90B_EntropyAssessment/wiki/Installing-libdivsufsort) for some distribution-specific instructions on installing divsufsort.

## Overview

* `bin/` has binary files for testing
* `cpp/` holds the new codebase

## How to run

The project is divided into two sections, IID tests and non-IID tests. They are intended to be separate. One provides an assurance that a dataset is IID [(independent and identically distributed)](https://en.wikipedia.org/wiki/Independent_and_identically_distributed_random_variables) and the other provides an estimate for min-entropy for any data provided. Please note that most commonly used entropy sources are not IID; see IG7.18 for the additional justification necessary to support any IID claim.

One can make all the binaries using:

	make

After compiling, one can test that your compilation behaves as expected by using the self-test functionality:
	cd selftest
	./selftest

Any observed delta less than 1.0E-6 is considered a pass for the self test.

For IID tests use the Makefile to compile the program:

    make iid

Then you can run the program with

    ./ea_iid [-i|-c] [-a|-t] [-v] [-l <index>,<samples>] <file_name> [bits_per_symbol]

You must specify either `-i` or `-c`, and either `-a` or `-t`. These correspond to the following:

* `-i`: Indicates the data is unconditioned and returns an initial entropy estimate. This is the default.
* `-c`: Indicates the data is conditioned
* `-a`: Estimates the entropy for all data in the binary file. This is the default.
* `-t`: Truncates the created bitstring representation of data to the first one million bits.
* `-l`: Reads (at most) `samples` data samples after indexing into the file by `index*samples` bytes.
* `-v: Optional verbosity flag for more output. Can be used multiple times.
* bits_per_symbol are the number of bits per symbol. Each symbol is expected to fit within a single byte.

To run the non-IID tests, use the Makefile to compile:

    make non_iid

Running this works the same way. This looks like

	./ea_non_iid [-i|-c] [-a|-t] [-v] [-l <index>,<samples> ] <file_name> [bits_per_symbol]

To run the restart testing, use the Makefile to compile:
    make restart

Running this is similar.
	./ea_restart [-i|-n] [-v] <file_name> [bits_per_symbol] <H_I>

* `-i`: Indicates IID data.
* `-n`: Indicates non-IID data.
* `-v`: Optional verbosity flag for more output. Can be used multiple times.
* bits_per_symbol are the number of bits per symbol. Each symbol is expected to fit within a single byte.
* `H_I` is the assessed entropy.

To calculate the entropy reduction due to conditioning, use the Makefile to compile:
    make conditioning

Running this is similar.
	./ea_conditioning [-v] <n_in> <n_out> <nw> <h_in>
	or
	ea_conditioning -n <n_in> <n_out> <nw> <h_in> <h'>

* `-v`: The conditioning function is vetted.
* `-n`: The conditioning function is non-vetted.
* `n_in`: The number of bits entering the conditioning step per output.
* `n_out`: The number of bits per conditioning step output.
* `nw`: The narrowest width of the conditioning step.
* `h_in`: The amount of entropy entering the conditioning step per output. Must be less than n_in.
* `h'`:  The entropy estimate per bit of conditioned sequential dataset (only for '-n' option).

## Make

A `Makefile` is provided.

## More Information

For more information on the estimation methods, see [SP 800-90B](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-90B.pdf).

## Contributions

Pull requests are welcome and will be reviewed before being merged. No timelines are promised. The code is maintained by Chris Celi (NIST).
