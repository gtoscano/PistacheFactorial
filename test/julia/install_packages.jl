# install_packages.jl

using Pkg

Pkg.activate("MyProject")  # Activate the environment

# Add the required packages
Pkg.add("HTTP")
Pkg.add("JSON")
