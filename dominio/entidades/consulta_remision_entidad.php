<?php

    class ConsultaRemisionEntidad {

        private FechasConsultaRemision $fechas;
        private $activity_num;
        private $tracks;

        public function __construct(
            $fechas = new FechasConsultaRemision(),
            $activity_num = '',
            $tracks = array(),
        )
        {
            $this->fechas = $fechas;
            $this->activity_num = $activity_num;
            $this->tracks = $tracks;
        }

        /**
         * Get the value of fechas
         */
        public function getFechas(): FechasConsultaRemision
        {
                return $this->fechas;
        }

        /**
         * Set the value of fechas
         */
        public function setFechas(FechasConsultaRemision $fechas): self
        {
                $this->fechas = $fechas;

                return $this;
        }

        /**
         * Get the value of activity_num
         */
        public function getActivityNum()
        {
                return $this->activity_num;
        }

        /**
         * Set the value of activity_num
         */
        public function setActivityNum($activity_num): self
        {
                $this->activity_num = $activity_num;

                return $this;
        }

        /**
         * Get the value of tracks
         */
        public function getTracks()
        {
                return $this->tracks;
        }

        /**
         * Set the value of tracks
         */
        public function setTracks($tracks): self
        {
                $this->tracks = $tracks;

                return $this;
        }

    }


    class FechasConsultaRemision {

        private $fechaEstimadaEntrega;
        private $fechaProcesoLogistico;
        private $fechaEntregaTransportadora;
        private $fechaEnTransito;
        private $fechaEnReparto;
        private $fechaEntregado;
        
        public function __construct() {
            $this->fechaEstimadaEntrega = '';
            $this->fechaProcesoLogistico = '';
            $this->fechaEntregaTransportadora = '';
            $this->fechaEnTransito = '';
            $this->fechaEnReparto = '';
            $this->fechaEntregado = '';
        }

        /**
         * Get the value of fechaProcesoLogistico
         */
        public function getFechaProcesoLogistico()
        {
                return $this->fechaProcesoLogistico;
        }

        /**
         * Set the value of fechaProcesoLogistico
         */
        public function setFechaProcesoLogistico($fechaProcesoLogistico): self
        {
                $this->fechaProcesoLogistico = $fechaProcesoLogistico;

                return $this;
        }

        /**
         * Get the value of fechaEntregaTransportadora
         */
        public function getFechaEntregaTransportadora()
        {
                return $this->fechaEntregaTransportadora;
        }

        /**
         * Set the value of fechaEntregaTransportadora
         */
        public function setFechaEntregaTransportadora($fechaEntregaTransportadora): self
        {
                $this->fechaEntregaTransportadora = $fechaEntregaTransportadora;

                return $this;
        }

        /**
         * Get the value of fechaEnTransito
         */
        public function getFechaEnTransito()
        {
                return $this->fechaEnTransito;
        }

        /**
         * Set the value of fechaEnTransito
         */
        public function setFechaEnTransito($fechaEnTransito): self
        {
                $this->fechaEnTransito = $fechaEnTransito;

                return $this;
        }

        /**
         * Get the value of fechaEnReparto
         */
        public function getFechaEnReparto()
        {
                return $this->fechaEnReparto;
        }

        /**
         * Set the value of fechaEnReparto
         */
        public function setFechaEnReparto($fechaEnReparto): self
        {
                $this->fechaEnReparto = $fechaEnReparto;

                return $this;
        }

        /**
         * Get the value of fechaEntregado
         */
        public function getFechaEntregado()
        {
                return $this->fechaEntregado;
        }

        /**
         * Set the value of fechaEntregado
         */
        public function setFechaEntregado($fechaEntregado): self
        {
                $this->fechaEntregado = $fechaEntregado;

                return $this;
        }

        /**
         * Get the value of fechaEstimadaEntrega
         */
        public function getFechaEstimadaEntrega()
        {
                return $this->fechaEstimadaEntrega;
        }

        /**
         * Set the value of fechaEstimadaEntrega
         */
        public function setFechaEstimadaEntrega($fechaEstimadaEntrega): self
        {
                $this->fechaEstimadaEntrega = $fechaEstimadaEntrega;

                return $this;
        }


    }
