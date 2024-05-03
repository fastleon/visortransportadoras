<?php

module_load_include('php', 'visorentregas', 'dominio\datasource\remision_datasource');

abstract class ServicioWebDrupal {

    static function llamarServicioWeb($propiedad, $params) {
        //Hacer consulta al servicio web
        try{
            $service = wsclient_service_load('toxementintranetrestservices_tms'); //Servicio configurado en Drupal
        }
        catch (WSClientException $exception) {
            drupal_set_message('No se pudo cargar el servicio REST configurado', 'error');
            return (FALSE);
        }
        // Realizar la consulta GET
        try {
            $response = $service->invoke($propiedad, $params);
        }
        catch (WSClientException $exception) {
            drupal_set_message('No hay respuesta del servidor REST o error en la solicitud', 'error');
            return (FALSE);
        }
        //ve_add_error($response, 'respuesta directa del servidor');
        return ($response);
    }

}

class RemisionDatasourceImpl extends RemisionDatasource {

    public function getEstadoEntrega($num_remision) {
        $params = array(
            'shipment' => $num_remision,
        );
        $response = ServicioWebDrupal::llamarServicioWeb('consultarEmbarque', $params);
        return $response;
    }

}
