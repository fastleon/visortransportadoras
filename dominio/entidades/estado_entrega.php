<?php

    class EstadoEntrega {

        private $fechas;
        private $remision;
        private $soportes;

        public function __construct(
            FechasConsultaRemision $fechas = null,
            $remision = '',
            $soportes = array()
        )
        {
            $this->fechas = $fechas ? $fechas : new FechasConsultaRemision();
            $this->remision = $remision;
            $this->soportes = $soportes;
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
         * Get the value of remision
         */
        public function getRemision()
        {
                return $this->remision;
        }

        /**
         * Set the value of remision
         */
        public function setRemision($remision)
        {
                $this->remision = $remision;
                return $this;
        }

        /**
         * Get the value of soportes
         */
        public function getSoportes()
        {
                return $this->soportes;
        }

        /**
         * Set the value of soportes
         */
        public function setSoportes($soportes)
        {
                $this->soportes = $soportes;
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
