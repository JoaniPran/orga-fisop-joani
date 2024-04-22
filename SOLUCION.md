# microlab

## (1) Transferencia entre registros (repaso de secuenciales)

**a) Transferencia de datos:**
   - `input_bit`: Representa el dato que se desea guardar en el registro.
   - `en_input_bit`: Controla la entrada del dato anterior. Un valor de 1 permite la entrada del dato `input_bit`, mientras que 0 no lo permite.
   - `w`: Controla si el registro guarda el valor enviado.
   - `en_out`: Controla si el valor se envía a la salida.
   - `clk`: Es el clock.

   **Salidas:**
   - `R0`, `R1`, `R2`: Salidas de visualización del registro (el dato guardado). Su output es el último del componente.

**b) Secuencia para que el registro R1 pase a tener el valor 1:**
   1. Activar el `clock`.
   2. Activar `input_bit`.
   3. Activar `en_input_bit`.
   4. Activar `w` del registro a 1.

**c) Resolución**

   -Las desactivaciones de `w` se realizan por precaución.
   -Mantenemos activado el `clock` para simplificar la secuencia.

   1. Activar `clock`.
   2. Activar `input_bit`.
   3. Activar `en_input_bit`.
   4. Activar `w` de `registro0`.
   5. (Se visualiza un 1 en `R0`).
   6. Desactivar `w` de `registro0`.
   7. Activar `w` de `registro1`.
   8. (Se visualiza un 1 en `R1`).
   9. Desactivar `input_bit`.
  10. Desactivar `w` de `registro1`.
  11. Activar `w` de `registro0`.
  12. (Se visualiza 0 en `R0`).
  13. Activar `input_bit`.
  14. Desactivar `w` de `registro0`.
  15. Activar `w` de `registro2`.
  16. (Se visualiza un 1 en `R2`).

## (2) OrgaSmall - Análisis

**a) Tamaño de la memoria:**
   El tamaño de la memoria es de 256x8 bits, es decir, 256 bytes, dado el tamaño de la palabra es de 8 bits, solo podemos crear 256 combinaciones(2⁸).

**b) Tamaño del PC:**
   El PC tiene un tamaño de 8 bits, correspondiente a la cantidad de bits de las direcciones en la arquitectura.

**c) Instrucciones nuevas respetando el formato de instrucción:**
   Se podrían agregar 10 nuevas instrucciones, dado que ya hay 22 declaradas y el máximo es de 32.

### Módulos indicados de hardware:

**a) PC (Contador de Programa):** La señal `inc` incrementa en uno el dato de dirección guardado en el PC.

**b) ALU (Unidad Aritmético Lógica):** `opw indica si se debe guardar el valor que le llega al registro de los flags. Juega el papel de w de los registros que vimos en el ejercicio1.

**c) MicroOrgaSmall (DataPath):**
  - La señal `DE_enOutImm` habilita la entrada al bus de un valor inmediato. Esto signiﬁca que podemos
ingresar al bus un valor que luego podemos usar para, por ejemplo, guardar en un registro, guardar en el
`PC`, etc.
  - La parte del circuito que indica que registro se va a leer es la entrada de `outData`, y la que indica que
registro se va a escribir es la de `inData`, ubicadas en el componente Registers.
  
**d) ControlUnit (Unidad de control):** Los saltos condicionales son 3, y todos tienen un mecanismo similar, pero considerando diferentes ﬂags. Se comportan como un JMP básico si está activo el ﬂag correspondiente.

El código del `JMP` es el siguiente:

```
PC_load DE_enOutImm
reset_microOp
```

La primera linea carga un valor inmediato al `PC`, y luego, en la segunda línea, se hace un fetch de esa nueva
operación.
Los saltos condicionales usan estas mismas dos líneas al ﬁnal de su ejecución. Por ejemplo, el código del `JC`
es el siguiente:

```
JC_microOp load_microOp
reset_microOp
DE_enOutImm PC_load
reset_microOp
```

La primera línea prende `JC_microOp` y `load_microOp`, con lo cual si el ﬂag de carry está prendido, no se
carga en el `microPC` la siguiente micro-instrucción, sino la tercera, que es el inicio de un `JMP` básico. Si el
ﬂag de carry no está prendido, entonces hace un fetch de la siguiente micro-instrucción sin efectuar el
salto.
Los demás saltos condicionales funcionan de la misma manera, pero con los ﬂags de zero y de negative.


## (3) Ensamblar y correr

**a) El código guarda los valores dados (0xFF y 0x11) en `R0` y `R1`, respectivamente. Luego, los suma y guarda el resultado en `R0`. Si se enciende el bit de carry, vuelve a la etiqueta `siguiente y realiza la suma entre el resultado anterior y `R1`, guardándolo denuevo en `R0`. Si esto no enciende el bit de carry, no se ejecuta el salto y pasa al último `JPM`, donde hace el salto a la etiqueta `halt`que es en si la misma, haciendo que quede en un loop.

**b) Ubicación de las instrucciones en la memoria:**
Cada instrucción ocupará 16 bits en la memoria, y estarán ubicadas secuencialmente. Las etiquetas se reemplazarán por la dirección de memoria donde comienza la instrucción siguiente. En este caso, `seguir` se reemplaza por `0x02`, y `siguiente` por `0x06`.

**c) Cantidad de ciclos de clock necesarios para llegar a la instrucción `JMP halt`:**
Para el último JMP halt` serían necesarios 45 ciclos de clock (finaliza en el ciclo 47).
 - fectch +5
 - JMP +2
 - fetch +5
 - SET +2
 - fetch + 5
 - SET +2
 - fetch +5
 - ADD +5 
 - fetch + 5
 - JC +4
 - fetch +5
 - JMP +2

**d) Cantidad de microinstrucciones necesarias para realizar el ADD y el salto:**
Para realizar el `ADD` son necesarias 5 microinstrucciones, mientras que para el salto `JMP` son necesarias 2.

## (4) Ampliando la máquina
