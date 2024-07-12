<?php

//Estos son los parametros que se deben configurar para que funcione el modulo

define ('VE_DEBUG_MODE', true);  //-> modo debug?
define ('VE_PRODUCCION', false);     // ambiente producción?
define ('VE_TIEMPO_RECARGA', 60); //segundos que guarda la ultima busqueda
define ('VE_BASE_IMAGE_URL', '');       //URL desde donde llamar las imagenes
define ('VE_LOCAL_IMAGE_URL', '/clientes/clientes/sites/default/files/clientes/tms/evidencias');       //URL desde donde llamar las imagenes en pruebas LOCALES
define ('VE_PRODUCCION_URL', 'http://ejemplo.com.co');                //URL del dominio
define ('VE_ARCHIVOS_ANEXOS_URL', 'ejemplo.com.co/system/files');     //URL FILES EN PRODUCCION
