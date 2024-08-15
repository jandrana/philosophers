# PTHREAD

## Content
 1. [General pthread functions](#general-pthread-functions)
 2. [Mutex functions](#mutex-functions)
 3. [Semaphore functions (bonus)](#semaphore-functions-bonus)
 4. [Fork/kill/exit/waitpid (bonus)](#forkkillexitwaitpid-bonus)

## General pthread functions
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


## Mutex functions

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


## Semaphore functions (bonus)

### Semaphores Overview

**Include requirements:**
```c
#include <fcntl.h>			/* For O_* constants -- for sem_open()*/
#include <sys/stat.h>		/* For mode constants -- for sem_open()*/
#include <semaphore.h>
```

**POSIX  semaphores** allow processes and threads to synchronize their ac‐
tions.

A semaphore is an integer whose value is never allowed to fall below
zero.  Two operations can be performed on semaphores: increment the
semaphore value by one `sem_post(3)`; and decrement the semaphore value
by one `sem_wait(3)`. If the value of a semaphore is currently zero,
then a `sem_wait(3)` operation will block until the value becomes greater
than zero.

POSIX semaphores come in two forms: named semaphores and unnamed sema‐
phores

1. **Named semaphores**
	A named semaphore is identified by a name of the form /somename;
	that is, a null-terminated string of up to `NAME_MAX-4` (i.e.,
	251) characters consisting of an initial slash, followed by one
	or more characters, none of which are slashes. Two processes
	can operate on the same named semaphore by passing the same name
	to `sem_open(3)`.

	The `sem_open(3)` function creates a new named semaphore or opens
	an existing named semaphore.  After the semaphore has been
	opened, it can be operated on using `sem_post(3)` and `sem_wait(3)`.
	When a process has finished using the semaphore, it can use
	`sem_close(3)` to close the semaphore. When all processes have
	finished using the semaphore, it can be removed from the system
	using `sem_unlink(3)`.

2. **Unnamed semaphores** (memory-based semaphores)
	Not allowed in this project (interesting to learn in the close future)

See `man sem_overview` for an overview of POSIX semaphores


### 1. **sem_open()** -- initialize and open a named semaphore

#### Prototype
```c
sem_t *sem_open(const char *name, int oflag);
sem_t *sem_open(const char *name, int oflag,
	mode_t mode, unsigned int value);
```
Creates a new POSIX semaphore or opens an existing sema‐phore.

 - The semaphore is identified by `name` (see [Overview](#semaphores-overview))

 - The `oflag` argument specifies flags that control the
 operation of the call. (Definitions in <fcntl.h>.)
 If `O_CREAT` is specified in `oflag`, then the semaphore is
	created if it does not already exist
 If both `O_CREAT` and `O_EXCL` are specified in `oflag`,
	then an error is returned if a semaphore with
  the given `name` already exists.
 - If `O_CREAT` is specified in `oflag`, two additional arguments must be supplied.
	The `mode` argument specifies the permissions to be placed on the new semaphore,
	as for `open(2)` (Definitions in <sys/stat.h>.)
	The `value` argument specifies the initial value for the new semaphore.
	If `O_CREAT` is specified, and a semaphore with the given name already exists,
	`mode` and `value` are ignored

For more information regarding `value` (needed when mode is `O_CREAT`):
 - See [Mode Values](#extra-note-for-sem_open-mode_t-mode-argument) 

#### Return Values:

**SUCCESS:** `sem_open()` returns the address of the new semaphore;
this address is used when calling other semaphore-related functions.

**ERROR:** `sem_open()` returns `SEM_FAILED`, with `errno` set to indicate the error.

##### Error Codes:
 - EACCES: The semaphore exists, but the caller does not have permission to open it.
 - EEXIST: Both O_CREAT and O_EXCL were specified in `oflag`, but a semaphore with this `name` already exists.
 - EINVAL(1): value was greater than `SEM_VALUE_MAX`
 - EINVAL(2): `name` consists of just "/", followed by no other characters.
 - EMFILE: The per-process limit on the number of open file descriptors has been reached.
 - ENAMETOOLONG: `name` was too long
 - ENFILE: The system-wide limit on the total number of open files has been reached.
 - ENOENT: The `O_CREAT` flag was not specified in `oflag` and no semaphore with this `name` exists;
 or, `O_CREAT` was specified, but `name` wasn't well formed.
 - ENOMEM: Out of memory


### 2. **sem_close()** -- close a named semaphore

#### Prototype
```c
int sem_close(sem_t *sem);
```
It closes the named semaphore referred to by `sem`, allowing any resources that
the system has allocated to the calling process for this semaphore to be freed.

#### Return Values:
**SUCCESS:** `sem_close()` returns 0
**ERROR:** -1, with `errno` set to indicate the error

##### Error Codes:
 - EINVAL: `sem` is not a valid semaphore


### 3. **sem_post()** -- unlock a semaphore

#### Prototype
```c
int sem_post(sem_t *sem);
```
It increments (unlocks) the semaphore pointed to by `sem`.
If the semaphore's value consequently becomes greater than zero, another process or
thread blocked in a `sem_wait(3)` call will be woken up and proceed to lock the semaphore.

#### Return Values:
**SUCCESS:** `sem_close()` returns 0
**ERROR:** -1, with `errno` set to indicate the error

##### Error Codes:
 - EINVAL: `sem` is not a valid semaphore
 - EOVERFLOW: The maximum allowable value for a semaphore would be exceeded.


### 4. **sem_wait()** -- lock a semaphore

#### Prototype
```c
int sem_wait(sem_t *sem);
```
It decrements (locks) the semaphore pointed to by `sem`.
If the semaphore's value is greater than zero, then the decrement proceeds,
and the function returns, immediately.
If the semaphore currently has the value zero, then the call blocks until either it
becomes possible to perform the decrement (i.e., the semaphore value rises above zero),
or a signal handler interrupts the call.

#### Return Values:
**SUCCESS:** `sem_close()` returns 0
**ERROR:** -1, with `errno` set to indicate the error

##### Error Codes:
 - EINTR: The call was interrupted by a signal handler
 - EINVAL: `sem` is not a valid semaphore

### 5. **sem_unlink()** -- remove a named semaphore

#### Prototype
```c
int sem_unlink(const char *name);
```
It removes the named semaphore referred to by `name`.
The semaphore name is removed immediately. The semaphore is destroyed once all other processes that have the semaphore open close it.

#### Return Values:
**SUCCESS:** `sem_close()` returns 0
**ERROR:** -1, with `errno` set to indicate the error

##### Error Codes:
 - EACCES: caller does not have permission to unlink this semaphore.
 - ENAMETOOLONG: `name` was too long
 - ENOENT: There is no semaphore with the given `name`
