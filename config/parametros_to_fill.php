<?php

//Estos son los parametros que se deben configurar para que funcione el modulo

define ('VE_DEBUG_MODE', true);  //-> modo debug?
define ('VE_TIEMPO_RECARGA', 60); //segundos que guarda la ultima busqueda

function getParametros() {
    return array(
        'base_url' => '',
        'base_image_url' => '',
        'service_name' => '',
        'shipment_value' => '',
    );
}