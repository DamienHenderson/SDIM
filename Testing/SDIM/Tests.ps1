Measure-Command {../../build/SDIMC/Release/SDIMC.exe hello_world.sdim -o hello_world.bin}
Measure-Command {../../build/SDIMVM/Release/SDIMVM.exe hello_world.bin}

Measure-Command {../../build/SDIMC/Release/SDIMC.exe fibonacci.sdim -o fibonacci.bin}
Measure-Command {../../build/SDIMVM/Release/SDIMVM.exe fibonacci.bin}

Measure-Command {../../build/SDIMC/Release/SDIMC.exe is_prime.sdim -o is_prime.bin}
Measure-Command {../../build/SDIMVM/Release/SDIMVM.exe is_prime.bin}
PAUSE