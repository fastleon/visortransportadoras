<?php

    class ConsultaRemisionEntidad {

        private $fechas;
        private $activity_num;
        private $tracks;

        public function __construct(
            FechasConsultaRemision $fechas = null,
            $activity_num = '',
            $tracks = array()
        )
        {
            $this->fechas = $fechas ? $fechas : new FechasConsultaRemision();
            $this->activity_num = $activity_num;
            $this->tracks = $tracks;
        }

        /**
         * Get the value of fechas
         */
        public function getFechas()
        {
                return $this->fechas;
        }

        /**
         * Set the value of fechas
         */
        public function setFechas(FechasConsultaRemision $fechas)
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
        public function setActivityNum($activity_num)
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
        public function setTracks($tracks)
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
        public function setFechaProcesoLogistico($fechaProcesoLogistico)
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
        public function setFechaEntregaTransportadora($fechaEntregaTransportadora)
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
        public function setFechaEnTransito($fechaEnTransito)
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
        public function setFechaEnReparto($fechaEnReparto)
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
        public function setFechaEntregado($fechaEntregado)
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
        public function setFechaEstimadaEntrega($fechaEstimadaEntrega)
        {
                $this->fechaEstimadaEntrega = $fechaEstimadaEntrega;

                return $this;
        }


    }
