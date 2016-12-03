#dfpga

##Fork

- Fork de [Nick Johnson a.k.a. Arachnid](https://github.com/Arachnid/dfpga)
- Fuente del articulo en el [Blog de Nick](http://blog.notdot.net/2012/10/Build-your-own-FPGA)

##Descripción

Implementación de una celda (slice) de un FPGA completamente con lógica discreta (componentes de la serie 7400), y un compilador para un dialecto HDL personalizado para la misma.

- discretefpga.brd y discretefpga.sch son los archivos para la tarjeta y el esquematico en Eagle.
- dhdl.py es el compilador HDL; para ejecutarlo ``python dhdl.py infile outfile``.
- Los archivos *.dhdl son scripts DHDL de ejemplo.
