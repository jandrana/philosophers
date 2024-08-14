# PTHREAD

## General allowed functions
### 1. **pthread_create()**

#### Prototype
```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine)(void *), void *arg);
```
Creates a new thread of execution.
The new thread starts execution by invoking `start_routine()`; where `arg` is passed as the sole argument of `start_routine()`.

#### Examples:
```c
pthread_t  thread;

pthread_create(&thread, NULL, &routine, &p_data);
```

#### Return Values:
 - 0: **OK**
 - !0: **Error Code**

##### Error Codes:
 - EAGAIN(1): Insufficient resources to create another thread.
 - EAGAIN(2): A system-imposed limit on the number of threads was met.
 - EINVAL: Incorrect value for argument
 - EPERM: No permission to set the scheduling policy and parameters specified in attr.

### 2. **pthread_join()**

#### Prototype
```c
int pthread_join(pthread_t thread, void **status);
```
It suspends execution of the calling thread until the target `thread` terminates unless it has already terminated.

#### Examples:

##### Code:
```c
void	*routine(void *arg)
{
	char	*ret_val;

	printf("routine() entered with arg %s\n", arg);
	ret_val = malloc(20);
	if (!ret_val)
		return (perror("ENOMEM: Out of Memory"), NULL);
	strcpy(ret_val, "Test");
	pthread_exit(ret_val);
}

int main(void)
{
	pthread_t  thread;
	void		*ret_val;

	if (pthread_create(&thread, NULL, routine, "hola"))
		return (perror("pthread_create() error"), 1);

	if (pthread_join(&thread, &ret))
		return (perror("pthread_create() error"), 3);

	printf("Thread exited with %s\n", ret);
}
```
##### Output:
```bash
routine() entered with arg hola
Thread exited with Test
```

#### Return Values:
 - 0: **OK**
 - -1: **KO** and sets errno to EDEADLK, EINVAL or ESRCH

### 3. **pthread_detach()**

#### Prototype
```c
int pthread_detach(pthread_t thread);
```
Marks a thread for deletion.


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

