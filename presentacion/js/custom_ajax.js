(function ($) {
    Drupal.behaviors.customAjaxButton = {
        attach: function (context, settings) {
            // Variable de estado
            var isAjaxRequestInProgress = false;

            // Seleccionar todos los botones de imagen con la clase específica
            $('.ajax-image-button', context).once('ajax-button').click(function (event) {

                // hay una solicitud AJAX?
                if (isAjaxRequestInProgress) {
                    return;
                }

                // Marca que una solicitud AJAX está en curso
                isAjaxRequestInProgress = true;

                var $button = $(this);
                // Deshabilitar el botón para evitar múltiples clics
                $button.prop('disabled', true);

                // Llama al sistema AJAX de Drupal
                Drupal.ajax[this.id].eventResponse(this, event);

                // Añadir un manejador para reactivar el botón y restablecer el estado una vez que la solicitud AJAX haya terminado
                $(document).ajaxComplete(function () {
                    isAjaxRequestInProgress = false;
                    $button.prop('disabled', false);
                });
            });
        }
    };
})(jQuery);
