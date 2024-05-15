<?php

function agrandar_imagen_callback($form, $form_state) {
  
  // Obtener el valor seleccionado del campo de selección
  $selected_image = $form_state['triggering_element']['#ajax']['params']['urlImage'];

  $image_markup = array(
    '#prefix' => '<div class="imagen-completa" id="imagen-container">',
    '#suffix' => '</div>',
    '#markup' => '<a href="'. $selected_image .'" target="_blank"><img src="' . $selected_image . '"></a>',
  );

  return $image_markup;

}


function buscador_entregas_form_validate($form, &$form_state) {
  
  //Revisar si la validacion se activa por un Ajax o un Submit
  if (isset($form_state['input']['_triggering_element_name'])) {
    // Ajax - no revisar nada
    return;
  } 
  
  $button_clicked = $form_state['triggering_element']['#name'];
  if ($button_clicked == 'Buscar' ) {
    // Submit  - Que sea un numero lo que se desea buscar
    $valores = $form_state['values'];
    $entero = intval($valores['numSeguimiento']);
    if ($entero === 0 && $valores['numSeguimiento'] !== "0") {
      form_set_error('numSeguimiento', t('debe ingresar un numero para realizar la busqueda'));
    } 
  }

}
  

function buscador_entregas_form_submit($form, &$form_state) {

  //Llamar dependencias
  module_load_include('inc', 'visorentregas', 'presentacion/buscador_entregas');
  module_load_include('php', 'visorentregas', 'infraestructura/datasource/remision_datasource_impl');
  module_load_include('php', 'visorentregas', 'infraestructura/models/estado_entrega_dto');
  
  $button_clicked = $form_state['triggering_element']['#name'];
  $remision = $form_state['values']['numSeguimiento'];

  switch ($button_clicked){
    case 'Buscar':
      $datasource = new RemisionDatasourceImpl();
      $response = $datasource->getEstadoEntrega($remision);

      //No hay conexion con el servidor
      if ( empty($response) ) {
        buscadorentregas_limpiar_datos();
        //drupal_set_message('No hay respuesta por parte del servidor', 'error');
        return;
      }

      //no hay resultados para la busqueda
      if ( empty($response['activity_num']) ){
        drupal_set_message('No hay resultados para el numero de entrega: '. $remision, 'warning');
        buscadorentregas_limpiar_datos();
      }

      $response_estado = EstadoEntregaDTO::create( $response );
      $estado_entrega = $response_estado->toEntity();
      $_SESSION['visorentrega']['resultado'] = serialize($estado_entrega);
      $_SESSION['visorentrega']['numero'] = $estado_entrega->getRemision();
      $_SESSION['visorentrega']['time'] = REQUEST_TIME;
      ve_add_error(REQUEST_TIME, 'time_submit');
      break;

    case 'Limpiar':
      ve_add_error('antes de limpiar');
      buscadorentregas_limpiar_datos();
      $form['visor_entrega_html']['txt_busqueda']['sub']['numSeguimiento']['#value'] = '';
      $form['visor_resultados']['informacion'] = array(); 
      $form['visor_resultados']['soportes']= array();
      break;

  }

}

function buscadorentregas_limpiar_datos() {
  ve_add_error('borrando datos');
  unset($_SESSION['visorentrega']['resultado']);
  unset($_SESSION['visorentrega']['numero']);
  unset($_SESSION['visorentrega']['time']); 
}