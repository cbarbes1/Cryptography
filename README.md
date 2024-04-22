# Cryptography

<img src="https://github.com/cbarbes1/Cryptography/assets/115114714/b8f43d69-ed55-4f7b-8958-3ae6328f7f53" height=300 />


## Language chosen: C++
The reason for the use of c++ is for ease of parallelism

## Semester Project
- Cluster setup with head node and 4 worker nodes
- Obtained document on setting up cluster
- Use the Cluster to Factor Numbers using elementary techniques in Comparison to Elliptic Curve Factorization

## Cluster Setup Instructions


### Status Check
```bash
systemctl status nfs-server

```
### restart server
```
sudo systemctl restart nfs-server

```

### Cyclic Dependency

```bash
sudo nano /etc/exports
# comment out: Cloud file that holds executables
sudo systemctl daemon-reload
sudo systemctl start nfs-server

```
