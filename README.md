# USB CDC Example for CH32V305FBP6 (USB HS)
# Ejemplo USB CDC para CH32V305FBP6 (USB HS)

[English](#english) | [Español](#español)

---
## English

### Important

This example is specific to the CH32V305FBP6, which ONLY has a USB HS (High Speed) controller.
Unlike other models in the family, this IC does not have USB FS (Full Speed).

### Required File Updates

This example modifies two key files from the original manufacturer example:

1. **main.c**: Modified to implement the "Hello World" sending functionality using USB CDC.
2. **ch32v30x_it.c**: Modified to implement our timing system for periodic message sending.

Make sure to use our versions of these files instead of the manufacturer's original ones, as they contain critical modifications for this example to work.

### Features

- Basic USB CDC device implementation using USB HS
- Sends "Hello World" every 5 seconds
- Code specific for CH32V305FBP6
- Bilingual comments (English/Spanish)

[rest of English section remains the same...]

---
## Español

### Importante

Este ejemplo es específico para el CH32V305FBP6, que SOLO cuenta con controlador USB HS (High Speed).
A diferencia de otros modelos de la familia, este IC no dispone de USB FS (Full Speed).

### Actualizaciones de Archivos Necesarias

Este ejemplo modifica dos archivos clave del ejemplo original del fabricante:

1. **main.c**: Modificado para implementar la funcionalidad de envío de "Hola Mundo" usando USB CDC.
2. **ch32v30x_it.c**: Modificado para implementar nuestro sistema de temporización para el envío periódico de mensajes.

Asegúrese de usar nuestras versiones de estos archivos en lugar de los originales del fabricante, ya que contienen modificaciones críticas para que este ejemplo funcione.

### Características

- Implementación de dispositivo USB CDC básico usando USB HS
- Envía "Hola Mundo" cada 5 segundos
- Código específico para CH32V305FBP6
- Comentarios bilingües (Español/Inglés)

[resto de la sección en español permanece igual...]

---
## Common Sections / Secciones Comunes

### Modified Files / Archivos Modificados
- main.c (implements USB CDC message sending / implementa envío de mensajes por USB CDC)
- ch32v30x_it.c (implements timing system / implementa sistema de temporización)

[rest of common sections remain the same...]