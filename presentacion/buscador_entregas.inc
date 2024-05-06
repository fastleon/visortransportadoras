<?php

function buscador_entregas_form($form, &$form_state) {
  // form_load_include('inc', 'visorentregas', 'presentacion/buscador_entregas');
  
  //Llamar CSS
  drupal_add_css(drupal_get_path('module', 'visorentregas') . '/presentacion/css/style_seguimiento.css');
  //Llamar dependencias
  form_load_include($form_state, 'inc', 'visorentregas', 'presentacion/buscador_entregas_submit');
  module_load_include('php', 'visorentregas', 'dominio/entidades/estado_entrega');
  module_load_include('php', 'visorentregas', 'infraestructura/datasource/remision_datasource_impl');
  module_load_include('php', 'visorentregas', 'infraestructura/models/estado_entrega_dto');
  
  $ubicacion_modulo = base_path() . drupal_get_path('module', 'visorentregas');
  $config = $_SESSION['visorentrega']['config'];
  $estado_entrega = new EstadoEntrega();

  //REVISAR SI YA SE HIZO UNA CONSULTA Y SI ESTA NO LLEVA MAS DEL TIEMPO PROGRAMADO
  if (isset($_SESSION['visorentrega']['numero'])) {
    if (isset($_SESSION['visorentrega']['time'])) {
      if (REQUEST_TIME - $_SESSION['visorentrega']['time'] > VE_TIEMPO_RECARGA) {
        unset($_SESSION['visorentrega']['numero']);
        unset($_SESSION['visorentrega']['time']);
        unset($_SESSION['visorentrega']['resultado']);
      }
    }
    if (isset($_SESSION['visorentrega']['resultado'])) {
      $temporal = unserialize($_SESSION['visorentrega']['resultado']);
      if ( !empty($temporal->getRemision()) ) {
        $estado_entrega = $temporal;
      }
    }
  }

  //CONTENIDO
  $form['visor_entrega_html'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="visor-entrega-html">',
    '#suffix' => '</div>'
  );

  //Banner
  $form['visor_entrega_html']['img_banner'] = buscador_banner($ubicacion_modulo);
  //Cuadro de texto
  $form['visor_entrega_html']['txt_busqueda'] = buscador_campo_texto()['contenedor_texfield'];
  //Botones de consulta
  $form['visor_entrega_html']['botones'] = buscador_botones()['visor_entrega_botones'];
  //resultados
  if ( !empty($estado_entrega->getRemision()) ) {
    $form['visor_resultados']['informacion'] = buscador_resultados($ubicacion_modulo, $estado_entrega);
  }

  if ( !empty($estado_entrega->getSoportes()) ) {
    $form['visor_resultados']['soportes'] = buscador_imagenes($estado_entrega->getSoportes())['soportes'];
  } else if ( !empty($estado_entrega->getRemision()) ) {
    $form['visor_resultados']['soportes'] = buscador_sin_soportes()['soportes'];
  }

  return $form;

}

function buscador_banner($ubicacion_modulo) {
  $html = '';
  $html .= '<section id="banner">';
  $html .= '  <div>';
  $html .= '    <div id="mensaje-banner">SEGUIMIENTO DE ENVÍOS</div>';
  $html .= '    <img id="banner-normal" src="'. $ubicacion_modulo .'/presentacion/img/Banner_Header.jpg" alt="BANNER"/>';
  $html .= '  </div>';
  $html .= '</section>';
  return array('#markup' => $html);
}

function buscador_campo_texto() {
  $cuadroTexto['contenedor_texfield'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="sec-consulta">',
    '#suffix' => '</div>'
  );
  $cuadroTexto['contenedor_texfield']['sub'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="con-num-seg-consulta">',
    '#suffix' => '</div>'
  );
  $cuadroTexto['contenedor_texfield']['sub']['numSeguimiento'] = array(
    '#type' => 'textfield',
    '#title' => t('N° de entrega'),
    //'#value' => '',
    '#required' => FALSE,
    '#disabled' => FALSE,
    '#maxlength' => 15,
    '#attributes' => array(
      'class' => array('text-h3'),
      'id' => 'num-seg-input',
      'placeholder' => 'Buscar # de seguimiento',
    ),
    '#prefix' => '<div id="num-seg-label">', // ID para el label
    '#suffix' => '</div>',
  );
//style="text-align: center;"></div>';
  
  return $cuadroTexto;
}

function buscador_botones() {
  $botones['visor_entrega_botones'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="visor-entrega-botones">',
    '#suffix' => '</div>'
  );
  $botones['visor_entrega_botones']['submit_buscar'] = array(
    '#name' => 'Buscar',
    '#type' => 'submit',
    '#value' => t('Buscar'),
  );
  $botones['visor_entrega_botones']['submit_limpiar'] = array(
    '#name' => 'Limpiar', 
    '#type' => 'submit',
    '#value' => t('Limpiar'),
  );
  return $botones;
}

function buscador_resultados($ubicacion_modulo, $estado_entrega) {
  //Traer informacion de sesion o busqueda reciente
  $fechas=$estado_entrega->getFechas();

  /*Saber si tiene datos de fechas*/
  $estadosEnvio = ['offset',
    empty($fechas->getFechaProcesoLogistico()) ? 'off' : 'on',
    empty($fechas->getFechaEntregaTransportadora()) ? 'off' : 'on',
    empty($fechas->getFechaEnTransito()) ? 'off' : 'on',
    empty($fechas->getFechaEnReparto()) ? 'off' : 'on',
    empty($fechas->getFechaEntregado()) ? 'off' : 'on'
  ];

  /*Metodo para saber que linea usar basandose en la ultima fecha no vacia*/
  $fechaActiva = 1;
  $i = count($estadosEnvio)-1;
  do{
      if ($estadosEnvio[$i] == "on"){
          $fechaActiva = $i;
          break;
      }
      $i--;
  }while($i >= 1);

  $html = <<<HTML
  <section id="sec-estado-envio";>
    <div class="back-verde-deg" id="con-num-order">
      Resultados para {$estado_entrega->getRemision()}
    </div>
    <div id="contenedor-resultados">
      <div id="con-fecha-entrega">
          <div class="text-h3" id="lbl-fecha-entrega">FECHA ESTIMADA DE ENTREGA</div>
          <div id="txt-fecha-entrega">{$fechas->getFechaEstimadaEntrega()}</div>
      </div>
      <div id="con-resultado-iconos">
        <div id="con-int-resultado-iconos">
          <div class="etapas" id="etapa-1">
            <div class="texto texto-sup texto-{$estadosEnvio[1]}">En proceso<br>logístico</div>
            <div class="icono"><img src="{$ubicacion_modulo}/presentacion/img/Icono_{$estadosEnvio[1]}_Estados_Envio_1.png" /></div> 
            <div class="texto fecha-inf fecha-{$estadosEnvio[1]}">{$fechas->getFechaProcesoLogistico()}</div>
          </div>
          <div id="etapa-separador"></div>
          <div class="etapas" id="etapa-2">
            <div class="texto texto-sup texto-{$estadosEnvio[2]}">Entrega a transportadora</div>
            <div class="icono"><img src="{$ubicacion_modulo}/presentacion/img/Icono_{$estadosEnvio[2]}_Estados_Envio_2.png" /></div> 
            <div class="texto fecha-inf fecha-{$estadosEnvio[2]}">{$fechas->getFechaEntregaTransportadora()}</div>
          </div>
          <div id="etapa-separador"></div>
          <div class="etapas" id="etapa-3">
            <div class="texto texto-sup texto-{$estadosEnvio[3]}">En tránsito<br>logístico</div>
            <div class="icono"><img src="{$ubicacion_modulo}/presentacion/img/Icono_{$estadosEnvio[3]}_Estados_Envio_3.png" /></div> 
            <div class="texto fecha-inf fecha-{$estadosEnvio[3]}">{$fechas->getFechaEnTransito()}</div>
          </div>
          <div id="etapa-separador"></div>
          <div class="etapas" id="etapa-4">
            <div id="sub-etapa-4">
            <div class="texto texto-sup texto-{$estadosEnvio[4]}" id="texto-mini-1">En reparto<br></div>
            <div class="texto texto-sup texto-{$estadosEnvio[4]}" id="texto-mini-2">(ciudad de destino)<br></div>
            </div>
            <div class="icono"><img src="{$ubicacion_modulo}/presentacion/img/Icono_{$estadosEnvio[4]}_Estados_Envio_4.png"/></div> 
            <div class="texto fecha-inf fecha-{$estadosEnvio[4]}">{$fechas->getFechaEnReparto()}</div>
          </div>
          <div id="etapa-separador"></div>
          <div class="etapas" id="etapa-5">
            <div class="texto texto-sup texto-{$estadosEnvio[5]}">Entregado</div>
            <div class="icono"><img src="{$ubicacion_modulo}/presentacion/img/Icono_{$estadosEnvio[5]}_Estados_Envio_5.png" /></div> 
            <div class="texto fecha-inf fecha-{$estadosEnvio[5]}">{$fechas->getfechaEntregado()}</div>
          </div>
        </div>
      </div>
    </div>
  </section>
HTML;

  return array('#markup' => $html); 

}

function buscador_imagenes($soportes) {

  $imagenes['soportes']['label'] = array(
    '#prefix' => '<div class="back-verde-deg" id="soportes-label">',
    '#suffix' => '</div>',
    '#markup' => 'SOPORTES',
  );

  $imagenes['soportes']['imagenes_wrapper'] = array(
    '#prefix' => '<div id="imagenes-wrapper">',
    '#suffix' => '</div>',
  );

  $i = 0;
  $nombreImagenes = array();
  foreach ($soportes as $soporte) {
    if (VE_PRODUCCION) {
      $soporte= str_replace(VE_PRODUCCION_URL, VE_BASE_IMAGE_URL, $soporte);
    }
    $imagenes['soportes']['imagenes_wrapper']['imagen'.$i++] = array(
      '#type' => 'image_button',
      '#src' => $soporte,
      '#name' => 'imagen'.$i,
      '#ajax' => array(
        'callback' => 'agrandar_imagen_callback',
        'wrapper' => 'imagen-container',
        'params' => array(
          'urlImage' => $soporte,
        ),
      ),
      '#attributes' => array(
        'class' => array('imagen-miniatura'),
      ),
    );
    $nombreImagenes[] = array($soporte => basename($soporte));
  }

  // $imagenes['soportes']['imagenes_wrapper']['select_image'] = array(
  //   '#type' => 'select',
  //   '#title' => 'Seleccione una imagen',
  //   '#options' => $nombreImagenes,
  //   '#element_validate' => array(),
  //   '#ajax' => array(
  //     'callback' => 'cambiar_imagen_callback',
  //     'wrapper' => 'imagen-container',
  //   ),
  // );
  
  $imagenes['soportes']['imagen-completa'] = array(
    '#prefix' => '<div id="imagen-container">',
    '#suffix' => '</div>',
    '#markup' => '',
  );

  return $imagenes;
}


function buscador_sin_soportes() {

  $imagenes['soportes']['label'] = array(
    '#prefix' => '<div class="back-gray-deg" id="soportes-label">',
    '#suffix' => '</div>',
    '#markup' => 'Entrega sin sopportes en el sistema',
  );

  return $imagenes;

}