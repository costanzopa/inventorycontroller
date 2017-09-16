#! /bin/bash

echo "Se inicia el proceso de creacion."

DEFAULT="install_dir"

if [ $# -eq 1 ]; then
	echo -e ""
	path_installer=$1
else 
	mkdir "install_dir"
	path_installer=$DEFAULT
	chmod 700 $path_installer
fi

echo "Se instalara en: ${path_installer}"

sleep 2

#make

sleep 5

clear

echo "Se va a iniciar el proceso de instalacion"


mkdir "${path_installer}/server"
mkdir "${path_installer}/client"
mkdir "${path_installer}/admin"

chmod 700 "${path_installer}/server"
chmod 700 "${path_installer}/client"
chmod 700 "${path_installer}/admin"

###########################################################
echo "Se va a instalar el servidor..."

cp -R "server/config" "${path_installer}/server"

cp -R "server/data" "${path_installer}/server"

cp "server/server" "${path_installer}/server"

chmod 700 "${path_installer}/server/server"

echo "Se ha instalado el servidor..."

######################################################

echo "Se va a instalar el Cliente..."

cp -R "client/ui" "${path_installer}/client"

cp -R "client/client" "${path_installer}/client"


chmod 700 "${path_installer}/client/client"

echo "Se ha instalado el Cliente..."

######################################################

echo "Se va a instalar el Administrador..."

cp -R "admin/datos" "${path_installer}/admin"

cp -R "admin/glade" "${path_installer}/admin"

cp "admin/admin" "${path_installer}/admin"

chmod 700 "${path_installer}/admin/admin"

echo "Se ha instalado el Administrador..."




