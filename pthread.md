# PTHREAD

## Mandatory allowed functions (mutex)

### 1. **pthread_mutex_init()**

#### Prototype
```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```

Initializes a mutex with the specified attributes. If `attr` is specified as `NULL`, all attributes are set to default.

#### Example: 
```c
pthread_mutex_t  mutex;
pthread_mutex_t  mutex2;
pthread_mutexattr_t   mta;

pthread_mutex_init(&mutex, NULL); // Atributes set to default
pthread_mutexattr_init(&mta); // Create a default mutex attribute
pthread_mutex_init(&mutex2, &mta); // Atributes set to mta (default attributes)
```
#### Return Values: 
 - 0: **OK**
 - !0: **Error Code**

##### Error Codes:
 - EINVAL: Incorrect value for argument
 - ENOMEM: Out of Memory

### 2. **pthread_mutex_destroy()**

#### Prototype
```c
int pthread_mutex_destroy(pthread_mutex_t *mutex); 
```
Destroys the named mutex and can no longer be used.


#### Example: 
```c
pthread_mutex_t  mutex;

pthread_mutex_init(&mutex, NULL);
pthread_mutex_destroy(&mutex);
```
#### Return Values: 
 - 0: **OK**
 - !0: **Error Code**

##### Error Codes:
 - EINVAL(1): Incorrect value for argument
 - EINVAL(2): Calling pthread_mutex_destroy() or pthread_mutex_unlock() on a mutex that has statically initialized using PTHREAD_MUTEX_INITIALIZER and was not yet locked.
 - EBUSY: If called on a mutex that is locked by another thread, the request fails with an EBUSY error. 
 - EDESTROYED: If the calling thread has the mutex locked, any other threads waiting for the mutex using a call to pthread_mutex_lock() at the time of the call fails.

	> [!NOTE]
	>  - Always use pthread_mutex_destroy() before freeing mutex storage to prevent debug LIC log entries
	>  - Once a mutex is created, it cannot be validly copied or moved to a new location.

### 3. **pthread_mutex_unlock()**

#### Prototype
```c
 int pthread_mutex_unlock(pthread_mutex_t *mutex); 

 Usage: pthread_mutex_unlock(&mutex);
```
The pthread_mutex_lock() unlocks the specified mutex.


#### Return Values: 
 - 0: **OK**
 - !0: **Error Code**

##### Error Codes:
 - EINVAL: Incorrect value for argument
 - EPERM: The mutex is not currently held by the caller.

