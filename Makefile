all:
	cd common; make common
	cd client; make 
	cd admin; make
	cd server; make server

clean:
	cd common; make clean
	cd server; make clean
