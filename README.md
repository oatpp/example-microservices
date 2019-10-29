# example-microservices

This is an example project on how to build microservices with Oat++ Web Framework, and how to utilize the [Monolithization](https://oatpp.io/docs/monolithization/) feature.

See more:

- [Oat++ Website](https://oatpp.io/)
- [Oat++ Github Repository](https://github.com/oatpp/oatpp)
- [Get Started](https://oatpp.io/docs/start)
- [Monolithization](https://oatpp.io/docs/monolithization/)

## Note

For more information about this example, see the [Monolithization](https://oatpp.io/docs/monolithization/) article.

## Inside This Repository

```
|- user-service/                          // User-Service source code
|- book-service/                          // Book-Service source code
|- facade/                                // Facade source code
|- monolith/all-services/                 // Monolithic config to build all services as a Monolith
|- build_all.sh                           // Utility script. Build all services
|- run_all_microservices.sh               // Utility script. Run all services as separate applications
```

## Build And Run

### Pre Requirements

- Install the [oatpp](https://github.com/oatpp/oatpp)
- Install the [oatpp-swagger](https://github.com/oatpp/oatpp-swagger)

### Build all

```bash
$ ./build_all.sh 
```

### Run as separate applications

```bash
$ ./run_all_microservices.sh 
```

### Run as monolith

```bash
$ ./monolith/all-services/build/all-services-exe
```
