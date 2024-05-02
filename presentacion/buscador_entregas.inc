<?php

function buscador_entregas_form($form, &$form_state) {

  //Llamar CSS
  drupal_add_css(drupal_get_path('module', 'visorentregas') . '/presentacion/css/style_seguimiento.css');
  //Llamar dependencias
  module_load_include('php', 'visorentregas', 'dominio\entidades\consulta_remision_entidad');
  
  $ubicacion_modulo = base_path() . drupal_get_path('module', 'visorentregas');
  $html = '';
  $resultado = new ConsultaRemisionEntidad();

  //REVISAR SI YA SE HIZO UNA CONSULTA Y SI ESTA NO LLEVA MAS DEL TIEMPO PROGRAMADO
  if (isset($_SESSION['visorentrega']['numero'])) {
    if (isset($_SESSION['visorentrega']['time'])) {
      if (REQUEST_TIME - $_SESSION['visorentrega']['time'] > VE_TIEMPO_RECARGA) {
        unset($_SESSION['visorentrega']['numero']);
        unset($_SESSION['visorentrega']['time']);
        unset($_SESSION['visorentrega']['resultado']);
      }
    }
    //TODO traer la informacion de la sesion confirmando el numero de entrega
  }

  //TEMPORAL
  $fechas = $resultado->getFechas();
  $fechas->setFechaEnReparto('03/03/2023');
  $fechas->setFechaEnTransito('04/03/2023');
  $fechas->setFechaEntregado('05/03/2023');
  $fechas->setFechaEntregaTransportadora('06/03/2023');
  $fechas->setFechaEstimadaEntrega('07/03/2023');
  $fechas->setFechaProcesoLogistico('08/03/2023');
  $resultado->setActivityNum('1111111');
  $resultado->setFechas($fechas);
  $_SESSION['visorentrega']['resultado'] = $resultado;

  //CONTENIDO
  $form['visor_entrega_html'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="visor-entrega-html">',
    '#suffix' => '</div>'
  );

  //Banner
  $form['visor_entrega_html']['img_banner'] = buscador_banner($ubicacion_modulo);
  //Cuadro de texto
  $form['visor_entrega_html']['txt_busqueda'] = buscador_campo_texto($ubicacion_modulo);
  //Botones de consulta
  $form['visor_entrega_botones'] = buscador_botones()['visor_entrega_botones'];
  //resultados
  $form['visor_resultados'] = buscador_resultados($ubicacion_modulo);
  
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
  $html = '';
  $html .= '<section id="sec-consulta">';
  $html .= '        <div id="con-num-seg-consulta">';
  $html .= '            <div class="text-h3" id="num-seg-label"><label >N° de entrega</label></div>';
  $html .= '            <div class="text-h3" id="num-seg-input"><input type="text" name="numSeguimiento" placeholder="Buscar # de seguimiento" style="text-align: center;"></div>';
  $html .= '        </div>';
  $html .= '</section>';
  return array('#markup' => $html);
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

function buscador_resultados($ubicacion_modulo) {
  if (!isset($_SESSION['visorentrega']['resultado'])) {
    return array();
  }
  $resultado = $_SESSION['visorentrega']['resultado'];
  $fechas=$resultado->getFechas();
  ve_add_error($ubicacion_modulo, 'ubicacion');

  /*Saber si tiene datos de fechas*/
  $estadosEnvio = ["on", "on", "on", "on", "on", "on"]; //TODO Verificar como se adapta
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

  ve_add_error($estadosEnvio, 'estados');

  $html = <<<HTML
  <section id="sec-estado-envio";>
    <div class="back-verde-deg" id="con-num-order">Resultados para {$resultado->getActivityNum()}</div>
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
    </div>
  </section>
HTML;

  return array('#markup' => $html); 

}


/*
                  <section id="sec-estado-envio" style="visibility: {$visibilidadSeccionFechas}; height: {$heightSeccionFechas};">
                    <div class="back-verde-deg" id="con-num-order">Resultados para {$numSeguimiento}</div>
                    <div id="contenedor-resultados">
                        <div id="con-fecha-entrega">
                            <div class="text-h3" id="lbl-fecha-entrega">FECHA ESTIMADA DE ENTREGA</div>
                            <div id="txt-fecha-entrega">{$fechasSeguimiento["fechaEstimadaEntrega"]}</div>
                        </div>
                        <div id="con-resultado-iconos">
                            <div id="con-int-resultado-iconos">
                                <div class="etapas" id="etapa-1">
                                    <div class="texto fecha-sup fecha-{$estadosEnvio[1]}">{$fechasSeguimiento["fechaProcesoLogístico"]}</div>
                                    <div class="icono"><img src="img/Icono_{$estadosEnvio[1]}_Estados_Envio_1.png" /></div> 
                                    <div class="texto texto-inf texto-{$estadosEnvio[1]}">En proceso<br>logístico</div>
                                </div>
                                <div class="etapas" id="etapa-2">
                                    <div class="texto texto-sup texto-{$estadosEnvio[2]}">Entrega a transportadora</div>
                                    <div class="icono"><img src="img/Icono_{$estadosEnvio[2]}_Estados_Envio_2.png" /></div> 
                                    <div class="texto fecha-inf fecha-{$estadosEnvio[2]}">{$fechasSeguimiento["fechaEntregaTransportadora"]}</div>
                                </div>
                                <div class="etapas" id="etapa-3">
                                    <div class="texto fecha-sup fecha-{$estadosEnvio[3]}">{$fechasSeguimiento["fechaEnTransito"]}</div>
                                    <div class="icono"><img src="img/Icono_{$estadosEnvio[3]}_Estados_Envio_3.png" /></div> 
                                    <div class="texto texto-inf texto-{$estadosEnvio[3]}">En tránsito<br>logístico</div>
                                </div>
                                <div class="etapas" id="etapa-4">
                                    <div id="sub-etapa-4">
                                    <div class="texto texto-sup texto-{$estadosEnvio[4]}" id="texto-mini-1">En reparto<br></div>
                                    <div class="texto texto-sup texto-{$estadosEnvio[4]}" id="texto-mini-2">(ciudad de destino)<br></div>
                                    </div>
                                    <div class="icono"><img src="img/Icono_{$estadosEnvio[4]}_Estados_Envio_4.png"/></div> 
                                    <div class="texto fecha-inf fecha-{$estadosEnvio[4]}">{$fechasSeguimiento["fechaEnReparto"]}</div>
                                </div>
                                <div class="etapas" id="etapa-5">
                                    <div class="texto fecha-sup fecha-{$estadosEnvio[5]}">{$fechasSeguimiento["fechaEntregado"]}</div>
                                    <div class="icono"><img src="img/Icono_{$estadosEnvio[5]}_Estados_Envio_5.png" /></div> 
                                    <div class="texto texto-inf texto-{$estadosEnvio[5]}">Entregado</div>
                                </div>
                                <div id="linea-seg">
                                    <img src="img/Linea_Seguimiento_Estados_Envio_{$fechaActiva}.png" />
                                </div>
                                <div id="linea-seg-responsive">
                                    <img src="img/Linea_Seguimiento_Responsive_Estados_Envio_{$fechaActiva}.jpg" />
                                </div>
                            </div>
                        </div>
HTML;

//Modificaciones acorde a dato de url soporte
        $soporte = <<<HTML
            <div id="con-resultado-soporte">
                <img src="img/Boton_off_Soporte.png" alt="sin imagen de soporte"/>
            </div>
HTML;
        if (count($urlSoporte)>0){
            $soporte = <<<HTML
                <div id="con-resultado-soporte">
                    <label for="btn-modal">
                        <img onmouseout="this.src='img/Boton_on_Soporte.png';" onmouseover="this.src='img/Boton_on_Soporte_HoverOver.png';" src="img/Boton_on_Soporte.png" onclick="actualSlide(1)"/>
                    </label>
                </div>
HTML;
*/