# Vault
<img src="imgs/main.png" width="95%">

<img src="imgs/entry.png" width="95%" />

# Overview
*Vault* is a Hardware based Password Manager. Vault performs this by 
running on a Raspberry Pi (RP) with Ubuntu Server LTS. This allows for 
passwords to be hardware contained. Additionally, this offers the 
power of modular encryption. This is done by allowing the user to 
configure what Multi Factor Authentication (MFA) devices they want 
to work with. For instance, if a user wishes to enable fingerprint 
and token authentication it will be allowed.

Vault will allow for this through a modular configuration in the 
CAD design. The future Vault design allows for slideable modules that attach
through USB-C. This allows the user to attach modules if they wish. For
instance, if a user wishes to install fingerprint they would gather the
materials (fingerprint sensor, CAD design, and wiring), solder and build the
module, then they can attach things to their Vault. This design takes
inspiration from industry leader *Framework* who is leading the way in
repairable hardware.

Currently Vault is still very early in its processing taking a lot of time to
develop a full fledged password manager. The working parts are the read/write
of JSON as well as the TUI.

# Dependencies

In order to run Vault these must be installed:

```bash
# Note: package manager and package names may differ on your system
> yay -S go boost libsodium
```

# Compilation
Recommended:

```bash
> mkdir -p build
> cd build
> cmake ..
> make -j`nproc`
```


Alternatively:

```bash
> make
> cd build
```

# Execution
```bash
> ./vault
```

# Future Development
## CAD Design
In Development.

## Modules
For now Vault aims at supporting a two modules: fingerprint and token
authenticator. The fingerprint sensor is still to be implemented work with
Vault. The token authenticator will be a keypass with an existing app such as
Duo Mobile or another authenticator application that is easy to enable.

# Dates
Start: July 2024

End: Till Death

# Contributors
Victor Perez Contreras
