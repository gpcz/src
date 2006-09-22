/*	$OpenBSD: syscallargs.h,v 1.98 2006/09/22 14:36:56 pedro Exp $	*/

/*
 * System call argument lists.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from;	OpenBSD: syscalls.master,v 1.85 2006/09/22 14:36:24 pedro Exp 
 */

#ifdef	syscallarg
#undef	syscallarg
#endif

#define	syscallarg(x)							\
	union {								\
		register_t pad;						\
		struct { x datum; } le;					\
		struct {						\
			int8_t pad[ (sizeof (register_t) < sizeof (x))	\
				? 0					\
				: sizeof (register_t) - sizeof (x)];	\
			x datum;					\
		} be;							\
	}

struct sys_exit_args {
	syscallarg(int) rval;
};

struct sys_read_args {
	syscallarg(int) fd;
	syscallarg(void *) buf;
	syscallarg(size_t) nbyte;
};

struct sys_write_args {
	syscallarg(int) fd;
	syscallarg(const void *) buf;
	syscallarg(size_t) nbyte;
};

struct sys_open_args {
	syscallarg(const char *) path;
	syscallarg(int) flags;
	syscallarg(mode_t) mode;
};

struct sys_close_args {
	syscallarg(int) fd;
};

struct sys_wait4_args {
	syscallarg(pid_t) pid;
	syscallarg(int *) status;
	syscallarg(int) options;
	syscallarg(struct rusage *) rusage;
};

struct compat_43_sys_creat_args {
	syscallarg(const char *) path;
	syscallarg(mode_t) mode;
};

struct sys_link_args {
	syscallarg(const char *) path;
	syscallarg(const char *) link;
};

struct sys_unlink_args {
	syscallarg(const char *) path;
};

struct sys_chdir_args {
	syscallarg(const char *) path;
};

struct sys_fchdir_args {
	syscallarg(int) fd;
};

struct sys_mknod_args {
	syscallarg(const char *) path;
	syscallarg(mode_t) mode;
	syscallarg(dev_t) dev;
};

struct sys_chmod_args {
	syscallarg(const char *) path;
	syscallarg(mode_t) mode;
};

struct sys_chown_args {
	syscallarg(const char *) path;
	syscallarg(uid_t) uid;
	syscallarg(gid_t) gid;
};

struct sys_obreak_args {
	syscallarg(char *) nsize;
};

struct compat_25_sys_getfsstat_args {
	syscallarg(struct statfs *) buf;
	syscallarg(long) bufsize;
	syscallarg(int) flags;
};

struct compat_43_sys_lseek_args {
	syscallarg(int) fd;
	syscallarg(long) offset;
	syscallarg(int) whence;
};

struct sys_mount_args {
	syscallarg(const char *) type;
	syscallarg(const char *) path;
	syscallarg(int) flags;
	syscallarg(void *) data;
};

struct sys_unmount_args {
	syscallarg(const char *) path;
	syscallarg(int) flags;
};

struct sys_setuid_args {
	syscallarg(uid_t) uid;
};

struct sys_ptrace_args {
	syscallarg(int) req;
	syscallarg(pid_t) pid;
	syscallarg(caddr_t) addr;
	syscallarg(int) data;
};

struct sys_recvmsg_args {
	syscallarg(int) s;
	syscallarg(struct msghdr *) msg;
	syscallarg(int) flags;
};

struct sys_sendmsg_args {
	syscallarg(int) s;
	syscallarg(const struct msghdr *) msg;
	syscallarg(int) flags;
};

struct sys_recvfrom_args {
	syscallarg(int) s;
	syscallarg(void *) buf;
	syscallarg(size_t) len;
	syscallarg(int) flags;
	syscallarg(struct sockaddr *) from;
	syscallarg(socklen_t *) fromlenaddr;
};

struct sys_accept_args {
	syscallarg(int) s;
	syscallarg(struct sockaddr *) name;
	syscallarg(socklen_t *) anamelen;
};

struct sys_getpeername_args {
	syscallarg(int) fdes;
	syscallarg(struct sockaddr *) asa;
	syscallarg(socklen_t *) alen;
};

struct sys_getsockname_args {
	syscallarg(int) fdes;
	syscallarg(struct sockaddr *) asa;
	syscallarg(socklen_t *) alen;
};

struct sys_access_args {
	syscallarg(const char *) path;
	syscallarg(int) flags;
};

struct sys_chflags_args {
	syscallarg(const char *) path;
	syscallarg(u_int) flags;
};

struct sys_fchflags_args {
	syscallarg(int) fd;
	syscallarg(u_int) flags;
};

struct sys_kill_args {
	syscallarg(int) pid;
	syscallarg(int) signum;
};

struct compat_43_sys_stat_args {
	syscallarg(const char *) path;
	syscallarg(struct stat43 *) ub;
};

struct compat_43_sys_lstat_args {
	syscallarg(char *) path;
	syscallarg(struct stat43 *) ub;
};

struct sys_dup_args {
	syscallarg(int) fd;
};

struct sys_profil_args {
	syscallarg(caddr_t) samples;
	syscallarg(size_t) size;
	syscallarg(u_long) offset;
	syscallarg(u_int) scale;
};

struct sys_ktrace_args {
	syscallarg(const char *) fname;
	syscallarg(int) ops;
	syscallarg(int) facs;
	syscallarg(pid_t) pid;
};

struct sys_sigaction_args {
	syscallarg(int) signum;
	syscallarg(const struct sigaction *) nsa;
	syscallarg(struct sigaction *) osa;
};

struct sys_sigprocmask_args {
	syscallarg(int) how;
	syscallarg(sigset_t) mask;
};

struct sys_getlogin_args {
	syscallarg(char *) namebuf;
	syscallarg(u_int) namelen;
};

struct sys_setlogin_args {
	syscallarg(const char *) namebuf;
};

struct sys_acct_args {
	syscallarg(const char *) path;
};

struct sys_osigaltstack_args {
	syscallarg(const struct osigaltstack *) nss;
	syscallarg(struct osigaltstack *) oss;
};

struct sys_ioctl_args {
	syscallarg(int) fd;
	syscallarg(u_long) com;
	syscallarg(void *) data;
};

struct sys_reboot_args {
	syscallarg(int) opt;
};

struct sys_revoke_args {
	syscallarg(const char *) path;
};

struct sys_symlink_args {
	syscallarg(const char *) path;
	syscallarg(const char *) link;
};

struct sys_readlink_args {
	syscallarg(const char *) path;
	syscallarg(char *) buf;
	syscallarg(size_t) count;
};

struct sys_execve_args {
	syscallarg(const char *) path;
	syscallarg(char *const *) argp;
	syscallarg(char *const *) envp;
};

struct sys_umask_args {
	syscallarg(mode_t) newmask;
};

struct sys_chroot_args {
	syscallarg(const char *) path;
};

struct compat_43_sys_fstat_args {
	syscallarg(int) fd;
	syscallarg(struct stat43 *) sb;
};

struct compat_43_sys_getkerninfo_args {
	syscallarg(int) op;
	syscallarg(char *) where;
	syscallarg(int *) size;
	syscallarg(int) arg;
};

struct compat_25_sys_omsync_args {
	syscallarg(caddr_t) addr;
	syscallarg(size_t) len;
};

struct sys_sbrk_args {
	syscallarg(int) incr;
};

struct sys_sstk_args {
	syscallarg(int) incr;
};

struct compat_43_sys_mmap_args {
	syscallarg(caddr_t) addr;
	syscallarg(size_t) len;
	syscallarg(int) prot;
	syscallarg(int) flags;
	syscallarg(int) fd;
	syscallarg(long) pos;
};

struct sys_ovadvise_args {
	syscallarg(int) anom;
};

struct sys_munmap_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
};

struct sys_mprotect_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) prot;
};

struct sys_madvise_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) behav;
};

struct sys_mincore_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(char *) vec;
};

struct sys_getgroups_args {
	syscallarg(int) gidsetsize;
	syscallarg(gid_t *) gidset;
};

struct sys_setgroups_args {
	syscallarg(int) gidsetsize;
	syscallarg(const gid_t *) gidset;
};

struct sys_setpgid_args {
	syscallarg(pid_t) pid;
	syscallarg(int) pgid;
};

struct sys_setitimer_args {
	syscallarg(int) which;
	syscallarg(const struct itimerval *) itv;
	syscallarg(struct itimerval *) oitv;
};

struct compat_25_sys_swapon_args {
	syscallarg(const char *) name;
};

struct sys_getitimer_args {
	syscallarg(int) which;
	syscallarg(struct itimerval *) itv;
};

struct compat_43_sys_gethostname_args {
	syscallarg(char *) hostname;
	syscallarg(u_int) len;
};

struct compat_43_sys_sethostname_args {
	syscallarg(char *) hostname;
	syscallarg(u_int) len;
};

struct sys_dup2_args {
	syscallarg(int) from;
	syscallarg(int) to;
};

struct sys_fcntl_args {
	syscallarg(int) fd;
	syscallarg(int) cmd;
	syscallarg(void *) arg;
};

struct sys_select_args {
	syscallarg(int) nd;
	syscallarg(fd_set *) in;
	syscallarg(fd_set *) ou;
	syscallarg(fd_set *) ex;
	syscallarg(struct timeval *) tv;
};

struct sys_fsync_args {
	syscallarg(int) fd;
};

struct sys_setpriority_args {
	syscallarg(int) which;
	syscallarg(id_t) who;
	syscallarg(int) prio;
};

struct sys_socket_args {
	syscallarg(int) domain;
	syscallarg(int) type;
	syscallarg(int) protocol;
};

struct sys_connect_args {
	syscallarg(int) s;
	syscallarg(const struct sockaddr *) name;
	syscallarg(socklen_t) namelen;
};

struct compat_43_sys_accept_args {
	syscallarg(int) s;
	syscallarg(caddr_t) name;
	syscallarg(int *) anamelen;
};

struct sys_getpriority_args {
	syscallarg(int) which;
	syscallarg(id_t) who;
};

struct compat_43_sys_send_args {
	syscallarg(int) s;
	syscallarg(caddr_t) buf;
	syscallarg(int) len;
	syscallarg(int) flags;
};

struct compat_43_sys_recv_args {
	syscallarg(int) s;
	syscallarg(caddr_t) buf;
	syscallarg(int) len;
	syscallarg(int) flags;
};

struct sys_sigreturn_args {
	syscallarg(struct sigcontext *) sigcntxp;
};

struct sys_bind_args {
	syscallarg(int) s;
	syscallarg(const struct sockaddr *) name;
	syscallarg(socklen_t) namelen;
};

struct sys_setsockopt_args {
	syscallarg(int) s;
	syscallarg(int) level;
	syscallarg(int) name;
	syscallarg(const void *) val;
	syscallarg(socklen_t) valsize;
};

struct sys_listen_args {
	syscallarg(int) s;
	syscallarg(int) backlog;
};

struct compat_43_sys_sigvec_args {
	syscallarg(int) signum;
	syscallarg(struct sigvec *) nsv;
	syscallarg(struct sigvec *) osv;
};

struct compat_43_sys_sigblock_args {
	syscallarg(int) mask;
};

struct compat_43_sys_sigsetmask_args {
	syscallarg(int) mask;
};

struct sys_sigsuspend_args {
	syscallarg(int) mask;
};

struct compat_43_sys_sigstack_args {
	syscallarg(struct sigstack *) nss;
	syscallarg(struct sigstack *) oss;
};

struct compat_43_sys_recvmsg_args {
	syscallarg(int) s;
	syscallarg(struct omsghdr *) msg;
	syscallarg(int) flags;
};

struct compat_43_sys_sendmsg_args {
	syscallarg(int) s;
	syscallarg(caddr_t) msg;
	syscallarg(int) flags;
};

struct sys_gettimeofday_args {
	syscallarg(struct timeval *) tp;
	syscallarg(struct timezone *) tzp;
};

struct sys_getrusage_args {
	syscallarg(int) who;
	syscallarg(struct rusage *) rusage;
};

struct sys_getsockopt_args {
	syscallarg(int) s;
	syscallarg(int) level;
	syscallarg(int) name;
	syscallarg(void *) val;
	syscallarg(socklen_t *) avalsize;
};

struct sys_readv_args {
	syscallarg(int) fd;
	syscallarg(const struct iovec *) iovp;
	syscallarg(int) iovcnt;
};

struct sys_writev_args {
	syscallarg(int) fd;
	syscallarg(const struct iovec *) iovp;
	syscallarg(int) iovcnt;
};

struct sys_settimeofday_args {
	syscallarg(const struct timeval *) tv;
	syscallarg(const struct timezone *) tzp;
};

struct sys_fchown_args {
	syscallarg(int) fd;
	syscallarg(uid_t) uid;
	syscallarg(gid_t) gid;
};

struct sys_fchmod_args {
	syscallarg(int) fd;
	syscallarg(mode_t) mode;
};

struct compat_43_sys_recvfrom_args {
	syscallarg(int) s;
	syscallarg(caddr_t) buf;
	syscallarg(size_t) len;
	syscallarg(int) flags;
	syscallarg(caddr_t) from;
	syscallarg(int *) fromlenaddr;
};

struct sys_setreuid_args {
	syscallarg(uid_t) ruid;
	syscallarg(uid_t) euid;
};

struct sys_setregid_args {
	syscallarg(gid_t) rgid;
	syscallarg(gid_t) egid;
};

struct sys_rename_args {
	syscallarg(const char *) from;
	syscallarg(const char *) to;
};

struct compat_43_sys_truncate_args {
	syscallarg(const char *) path;
	syscallarg(long) length;
};

struct compat_43_sys_ftruncate_args {
	syscallarg(int) fd;
	syscallarg(long) length;
};

struct sys_flock_args {
	syscallarg(int) fd;
	syscallarg(int) how;
};

struct sys_mkfifo_args {
	syscallarg(const char *) path;
	syscallarg(mode_t) mode;
};

struct sys_sendto_args {
	syscallarg(int) s;
	syscallarg(const void *) buf;
	syscallarg(size_t) len;
	syscallarg(int) flags;
	syscallarg(const struct sockaddr *) to;
	syscallarg(socklen_t) tolen;
};

struct sys_shutdown_args {
	syscallarg(int) s;
	syscallarg(int) how;
};

struct sys_socketpair_args {
	syscallarg(int) domain;
	syscallarg(int) type;
	syscallarg(int) protocol;
	syscallarg(int *) rsv;
};

struct sys_mkdir_args {
	syscallarg(const char *) path;
	syscallarg(mode_t) mode;
};

struct sys_rmdir_args {
	syscallarg(const char *) path;
};

struct sys_utimes_args {
	syscallarg(const char *) path;
	syscallarg(const struct timeval *) tptr;
};

struct sys_adjtime_args {
	syscallarg(const struct timeval *) delta;
	syscallarg(struct timeval *) olddelta;
};

struct compat_43_sys_getpeername_args {
	syscallarg(int) fdes;
	syscallarg(caddr_t) asa;
	syscallarg(socklen_t *) alen;
};

struct compat_43_sys_sethostid_args {
	syscallarg(int32_t) hostid;
};

struct compat_43_sys_getrlimit_args {
	syscallarg(int) which;
	syscallarg(struct ogetrlimit *) rlp;
};

struct compat_43_sys_setrlimit_args {
	syscallarg(int) which;
	syscallarg(struct ogetrlimit *) rlp;
};

struct compat_43_sys_killpg_args {
	syscallarg(int) pgid;
	syscallarg(int) signum;
};

struct sys_quotactl_args {
	syscallarg(const char *) path;
	syscallarg(int) cmd;
	syscallarg(int) uid;
	syscallarg(char *) arg;
};

struct compat_43_sys_getsockname_args {
	syscallarg(int) fdec;
	syscallarg(caddr_t) asa;
	syscallarg(int *) alen;
};

struct sys_nfssvc_args {
	syscallarg(int) flag;
	syscallarg(void *) argp;
};

struct compat_43_sys_getdirentries_args {
	syscallarg(int) fd;
	syscallarg(char *) buf;
	syscallarg(int) count;
	syscallarg(long *) basep;
};

struct compat_25_sys_statfs_args {
	syscallarg(const char *) path;
	syscallarg(struct ostatfs *) buf;
};

struct compat_25_sys_fstatfs_args {
	syscallarg(int) fd;
	syscallarg(struct ostatfs *) buf;
};

struct sys_getfh_args {
	syscallarg(const char *) fname;
	syscallarg(fhandle_t *) fhp;
};

struct compat_09_sys_getdomainname_args {
	syscallarg(char *) domainname;
	syscallarg(int) len;
};

struct compat_09_sys_setdomainname_args {
	syscallarg(char *) domainname;
	syscallarg(int) len;
};

struct compat_09_sys_uname_args {
	syscallarg(struct outsname *) name;
};

struct sys_sysarch_args {
	syscallarg(int) op;
	syscallarg(void *) parms;
};

struct compat_10_sys_semsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
	syscallarg(int) a5;
};

struct compat_10_sys_msgsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
	syscallarg(int) a5;
	syscallarg(int) a6;
};

struct compat_10_sys_shmsys_args {
	syscallarg(int) which;
	syscallarg(int) a2;
	syscallarg(int) a3;
	syscallarg(int) a4;
};

struct sys_pread_args {
	syscallarg(int) fd;
	syscallarg(void *) buf;
	syscallarg(size_t) nbyte;
	syscallarg(int) pad;
	syscallarg(off_t) offset;
};

struct sys_pwrite_args {
	syscallarg(int) fd;
	syscallarg(const void *) buf;
	syscallarg(size_t) nbyte;
	syscallarg(int) pad;
	syscallarg(off_t) offset;
};

struct sys_setgid_args {
	syscallarg(gid_t) gid;
};

struct sys_setegid_args {
	syscallarg(gid_t) egid;
};

struct sys_seteuid_args {
	syscallarg(uid_t) euid;
};

struct compat_35_sys_stat_args {
	syscallarg(const char *) path;
	syscallarg(struct stat35 *) ub;
};

struct compat_35_sys_fstat_args {
	syscallarg(int) fd;
	syscallarg(struct stat35 *) sb;
};

struct compat_35_sys_lstat_args {
	syscallarg(const char *) path;
	syscallarg(struct stat35 *) ub;
};

struct sys_pathconf_args {
	syscallarg(const char *) path;
	syscallarg(int) name;
};

struct sys_fpathconf_args {
	syscallarg(int) fd;
	syscallarg(int) name;
};

struct sys_swapctl_args {
	syscallarg(int) cmd;
	syscallarg(const void *) arg;
	syscallarg(int) misc;
};

struct sys_getrlimit_args {
	syscallarg(int) which;
	syscallarg(struct rlimit *) rlp;
};

struct sys_setrlimit_args {
	syscallarg(int) which;
	syscallarg(const struct rlimit *) rlp;
};

struct sys_getdirentries_args {
	syscallarg(int) fd;
	syscallarg(char *) buf;
	syscallarg(int) count;
	syscallarg(long *) basep;
};

struct sys_mmap_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) prot;
	syscallarg(int) flags;
	syscallarg(int) fd;
	syscallarg(long) pad;
	syscallarg(off_t) pos;
};

struct sys_lseek_args {
	syscallarg(int) fd;
	syscallarg(int) pad;
	syscallarg(off_t) offset;
	syscallarg(int) whence;
};

struct sys_truncate_args {
	syscallarg(const char *) path;
	syscallarg(int) pad;
	syscallarg(off_t) length;
};

struct sys_ftruncate_args {
	syscallarg(int) fd;
	syscallarg(int) pad;
	syscallarg(off_t) length;
};

struct sys___sysctl_args {
	syscallarg(int *) name;
	syscallarg(u_int) namelen;
	syscallarg(void *) old;
	syscallarg(size_t *) oldlenp;
	syscallarg(void *) new;
	syscallarg(size_t) newlen;
};

struct sys_mlock_args {
	syscallarg(const void *) addr;
	syscallarg(size_t) len;
};

struct sys_munlock_args {
	syscallarg(const void *) addr;
	syscallarg(size_t) len;
};

struct sys_futimes_args {
	syscallarg(int) fd;
	syscallarg(const struct timeval *) tptr;
};

struct sys_getpgid_args {
	syscallarg(pid_t) pid;
};

struct sys_xfspioctl_args {
	syscallarg(int) operation;
	syscallarg(char *) a_pathP;
	syscallarg(int) a_opcode;
	syscallarg(struct ViceIoctl *) a_paramsP;
	syscallarg(int) a_followSymlinks;
};

struct compat_23_sys___semctl_args {
	syscallarg(int) semid;
	syscallarg(int) semnum;
	syscallarg(int) cmd;
	syscallarg(union semun *) arg;
};

struct sys_semget_args {
	syscallarg(key_t) key;
	syscallarg(int) nsems;
	syscallarg(int) semflg;
};

struct compat_35_sys_semop_args {
	syscallarg(int) semid;
	syscallarg(struct sembuf *) sops;
	syscallarg(u_int) nsops;
};

struct compat_23_sys_msgctl_args {
	syscallarg(int) msqid;
	syscallarg(int) cmd;
	syscallarg(struct omsqid_ds *) buf;
};

struct sys_msgget_args {
	syscallarg(key_t) key;
	syscallarg(int) msgflg;
};

struct sys_msgsnd_args {
	syscallarg(int) msqid;
	syscallarg(const void *) msgp;
	syscallarg(size_t) msgsz;
	syscallarg(int) msgflg;
};

struct sys_msgrcv_args {
	syscallarg(int) msqid;
	syscallarg(void *) msgp;
	syscallarg(size_t) msgsz;
	syscallarg(long) msgtyp;
	syscallarg(int) msgflg;
};

struct sys_shmat_args {
	syscallarg(int) shmid;
	syscallarg(const void *) shmaddr;
	syscallarg(int) shmflg;
};

struct compat_23_sys_shmctl_args {
	syscallarg(int) shmid;
	syscallarg(int) cmd;
	syscallarg(struct oshmid_ds *) buf;
};

struct sys_shmdt_args {
	syscallarg(const void *) shmaddr;
};

struct compat_35_sys_shmget_args {
	syscallarg(key_t) key;
	syscallarg(int) size;
	syscallarg(int) shmflg;
};

struct sys_clock_gettime_args {
	syscallarg(clockid_t) clock_id;
	syscallarg(struct timespec *) tp;
};

struct sys_clock_settime_args {
	syscallarg(clockid_t) clock_id;
	syscallarg(const struct timespec *) tp;
};

struct sys_clock_getres_args {
	syscallarg(clockid_t) clock_id;
	syscallarg(struct timespec *) tp;
};

struct sys_nanosleep_args {
	syscallarg(const struct timespec *) rqtp;
	syscallarg(struct timespec *) rmtp;
};

struct sys_minherit_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) inherit;
};

struct sys_rfork_args {
	syscallarg(int) flags;
};

struct sys_poll_args {
	syscallarg(struct pollfd *) fds;
	syscallarg(u_int) nfds;
	syscallarg(int) timeout;
};

struct sys_lchown_args {
	syscallarg(const char *) path;
	syscallarg(uid_t) uid;
	syscallarg(gid_t) gid;
};

struct sys_getsid_args {
	syscallarg(pid_t) pid;
};

struct sys_msync_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) flags;
};

struct compat_35_sys___semctl_args {
	syscallarg(int) semid;
	syscallarg(int) semnum;
	syscallarg(int) cmd;
	syscallarg(union semun *) arg;
};

struct compat_35_sys_shmctl_args {
	syscallarg(int) shmid;
	syscallarg(int) cmd;
	syscallarg(struct shmid_ds35 *) buf;
};

struct compat_35_sys_msgctl_args {
	syscallarg(int) msqid;
	syscallarg(int) cmd;
	syscallarg(struct msqid_ds35 *) buf;
};

struct sys_getfsstat_args {
	syscallarg(struct statfs *) buf;
	syscallarg(size_t) bufsize;
	syscallarg(int) flags;
};

struct sys_statfs_args {
	syscallarg(const char *) path;
	syscallarg(struct statfs *) buf;
};

struct sys_fstatfs_args {
	syscallarg(int) fd;
	syscallarg(struct statfs *) buf;
};

struct sys_pipe_args {
	syscallarg(int *) fdp;
};

struct sys_fhopen_args {
	syscallarg(const fhandle_t *) fhp;
	syscallarg(int) flags;
};

struct compat_35_sys_fhstat_args {
	syscallarg(const fhandle_t *) fhp;
	syscallarg(struct stat35 *) sb;
};

struct sys_fhstatfs_args {
	syscallarg(const fhandle_t *) fhp;
	syscallarg(struct statfs *) buf;
};

struct sys_preadv_args {
	syscallarg(int) fd;
	syscallarg(const struct iovec *) iovp;
	syscallarg(int) iovcnt;
	syscallarg(int) pad;
	syscallarg(off_t) offset;
};

struct sys_pwritev_args {
	syscallarg(int) fd;
	syscallarg(const struct iovec *) iovp;
	syscallarg(int) iovcnt;
	syscallarg(int) pad;
	syscallarg(off_t) offset;
};

struct sys_kevent_args {
	syscallarg(int) fd;
	syscallarg(const struct kevent *) changelist;
	syscallarg(int) nchanges;
	syscallarg(struct kevent *) eventlist;
	syscallarg(int) nevents;
	syscallarg(const struct timespec *) timeout;
};

struct sys_mlockall_args {
	syscallarg(int) flags;
};

struct sys_getpeereid_args {
	syscallarg(int) fdes;
	syscallarg(uid_t *) euid;
	syscallarg(gid_t *) egid;
};

struct sys_getresuid_args {
	syscallarg(uid_t *) ruid;
	syscallarg(uid_t *) euid;
	syscallarg(uid_t *) suid;
};

struct sys_setresuid_args {
	syscallarg(uid_t) ruid;
	syscallarg(uid_t) euid;
	syscallarg(uid_t) suid;
};

struct sys_getresgid_args {
	syscallarg(gid_t *) rgid;
	syscallarg(gid_t *) egid;
	syscallarg(gid_t *) sgid;
};

struct sys_setresgid_args {
	syscallarg(gid_t) rgid;
	syscallarg(gid_t) egid;
	syscallarg(gid_t) sgid;
};

struct sys_mquery_args {
	syscallarg(void *) addr;
	syscallarg(size_t) len;
	syscallarg(int) prot;
	syscallarg(int) flags;
	syscallarg(int) fd;
	syscallarg(long) pad;
	syscallarg(off_t) pos;
};

struct sys_closefrom_args {
	syscallarg(int) fd;
};

struct sys_sigaltstack_args {
	syscallarg(const struct sigaltstack *) nss;
	syscallarg(struct sigaltstack *) oss;
};

struct sys_shmget_args {
	syscallarg(key_t) key;
	syscallarg(size_t) size;
	syscallarg(int) shmflg;
};

struct sys_semop_args {
	syscallarg(int) semid;
	syscallarg(struct sembuf *) sops;
	syscallarg(size_t) nsops;
};

struct sys_stat_args {
	syscallarg(const char *) path;
	syscallarg(struct stat *) ub;
};

struct sys_fstat_args {
	syscallarg(int) fd;
	syscallarg(struct stat *) sb;
};

struct sys_lstat_args {
	syscallarg(const char *) path;
	syscallarg(struct stat *) ub;
};

struct sys_fhstat_args {
	syscallarg(const fhandle_t *) fhp;
	syscallarg(struct stat *) sb;
};

struct sys___semctl_args {
	syscallarg(int) semid;
	syscallarg(int) semnum;
	syscallarg(int) cmd;
	syscallarg(union semun *) arg;
};

struct sys_shmctl_args {
	syscallarg(int) shmid;
	syscallarg(int) cmd;
	syscallarg(struct shmid_ds *) buf;
};

struct sys_msgctl_args {
	syscallarg(int) msqid;
	syscallarg(int) cmd;
	syscallarg(struct msqid_ds *) buf;
};

struct sys_thrsleep_args {
	syscallarg(void *) ident;
	syscallarg(int) timeout;
	syscallarg(void *) lock;
};

struct sys_thrwakeup_args {
	syscallarg(void *) ident;
	syscallarg(int) n;
};

struct sys_threxit_args {
	syscallarg(int) rval;
};

struct sys_thrsigdivert_args {
	syscallarg(sigset_t) sigmask;
};

struct sys___getcwd_args {
	syscallarg(char *) buf;
	syscallarg(size_t) len;
};

struct sys_adjfreq_args {
	syscallarg(const int64_t *) freq;
	syscallarg(int64_t *) oldfreq;
};

/*
 * System call prototypes.
 */

int	sys_exit(struct proc *, void *, register_t *);
int	sys_fork(struct proc *, void *, register_t *);
int	sys_read(struct proc *, void *, register_t *);
int	sys_write(struct proc *, void *, register_t *);
int	sys_open(struct proc *, void *, register_t *);
int	sys_close(struct proc *, void *, register_t *);
int	sys_wait4(struct proc *, void *, register_t *);
int	compat_43_sys_creat(struct proc *, void *, register_t *);
int	sys_link(struct proc *, void *, register_t *);
int	sys_unlink(struct proc *, void *, register_t *);
int	sys_chdir(struct proc *, void *, register_t *);
int	sys_fchdir(struct proc *, void *, register_t *);
int	sys_mknod(struct proc *, void *, register_t *);
int	sys_chmod(struct proc *, void *, register_t *);
int	sys_chown(struct proc *, void *, register_t *);
int	sys_obreak(struct proc *, void *, register_t *);
int	compat_25_sys_getfsstat(struct proc *, void *, register_t *);
int	compat_43_sys_lseek(struct proc *, void *, register_t *);
int	sys_getpid(struct proc *, void *, register_t *);
int	sys_mount(struct proc *, void *, register_t *);
int	sys_unmount(struct proc *, void *, register_t *);
int	sys_setuid(struct proc *, void *, register_t *);
int	sys_getuid(struct proc *, void *, register_t *);
int	sys_geteuid(struct proc *, void *, register_t *);
#ifdef PTRACE
int	sys_ptrace(struct proc *, void *, register_t *);
#else
#endif
int	sys_recvmsg(struct proc *, void *, register_t *);
int	sys_sendmsg(struct proc *, void *, register_t *);
int	sys_recvfrom(struct proc *, void *, register_t *);
int	sys_accept(struct proc *, void *, register_t *);
int	sys_getpeername(struct proc *, void *, register_t *);
int	sys_getsockname(struct proc *, void *, register_t *);
int	sys_access(struct proc *, void *, register_t *);
int	sys_chflags(struct proc *, void *, register_t *);
int	sys_fchflags(struct proc *, void *, register_t *);
int	sys_sync(struct proc *, void *, register_t *);
int	sys_kill(struct proc *, void *, register_t *);
int	compat_43_sys_stat(struct proc *, void *, register_t *);
int	sys_getppid(struct proc *, void *, register_t *);
int	compat_43_sys_lstat(struct proc *, void *, register_t *);
int	sys_dup(struct proc *, void *, register_t *);
int	sys_opipe(struct proc *, void *, register_t *);
int	sys_getegid(struct proc *, void *, register_t *);
int	sys_profil(struct proc *, void *, register_t *);
#ifdef KTRACE
int	sys_ktrace(struct proc *, void *, register_t *);
#else
#endif
int	sys_sigaction(struct proc *, void *, register_t *);
int	sys_getgid(struct proc *, void *, register_t *);
int	sys_sigprocmask(struct proc *, void *, register_t *);
int	sys_getlogin(struct proc *, void *, register_t *);
int	sys_setlogin(struct proc *, void *, register_t *);
#ifdef ACCOUNTING
int	sys_acct(struct proc *, void *, register_t *);
#else
#endif
int	sys_sigpending(struct proc *, void *, register_t *);
int	sys_osigaltstack(struct proc *, void *, register_t *);
int	sys_ioctl(struct proc *, void *, register_t *);
int	sys_reboot(struct proc *, void *, register_t *);
int	sys_revoke(struct proc *, void *, register_t *);
int	sys_symlink(struct proc *, void *, register_t *);
int	sys_readlink(struct proc *, void *, register_t *);
int	sys_execve(struct proc *, void *, register_t *);
int	sys_umask(struct proc *, void *, register_t *);
int	sys_chroot(struct proc *, void *, register_t *);
int	compat_43_sys_fstat(struct proc *, void *, register_t *);
int	compat_43_sys_getkerninfo(struct proc *, void *, register_t *);
int	compat_43_sys_getpagesize(struct proc *, void *, register_t *);
int	compat_25_sys_omsync(struct proc *, void *, register_t *);
int	sys_vfork(struct proc *, void *, register_t *);
int	sys_sbrk(struct proc *, void *, register_t *);
int	sys_sstk(struct proc *, void *, register_t *);
int	compat_43_sys_mmap(struct proc *, void *, register_t *);
int	sys_ovadvise(struct proc *, void *, register_t *);
int	sys_munmap(struct proc *, void *, register_t *);
int	sys_mprotect(struct proc *, void *, register_t *);
int	sys_madvise(struct proc *, void *, register_t *);
int	sys_mincore(struct proc *, void *, register_t *);
int	sys_getgroups(struct proc *, void *, register_t *);
int	sys_setgroups(struct proc *, void *, register_t *);
int	sys_getpgrp(struct proc *, void *, register_t *);
int	sys_setpgid(struct proc *, void *, register_t *);
int	sys_setitimer(struct proc *, void *, register_t *);
int	compat_43_sys_wait(struct proc *, void *, register_t *);
int	compat_25_sys_swapon(struct proc *, void *, register_t *);
int	sys_getitimer(struct proc *, void *, register_t *);
int	compat_43_sys_gethostname(struct proc *, void *, register_t *);
int	compat_43_sys_sethostname(struct proc *, void *, register_t *);
int	compat_43_sys_getdtablesize(struct proc *, void *, register_t *);
int	sys_dup2(struct proc *, void *, register_t *);
int	sys_fcntl(struct proc *, void *, register_t *);
int	sys_select(struct proc *, void *, register_t *);
int	sys_fsync(struct proc *, void *, register_t *);
int	sys_setpriority(struct proc *, void *, register_t *);
int	sys_socket(struct proc *, void *, register_t *);
int	sys_connect(struct proc *, void *, register_t *);
int	compat_43_sys_accept(struct proc *, void *, register_t *);
int	sys_getpriority(struct proc *, void *, register_t *);
int	compat_43_sys_send(struct proc *, void *, register_t *);
int	compat_43_sys_recv(struct proc *, void *, register_t *);
int	sys_sigreturn(struct proc *, void *, register_t *);
int	sys_bind(struct proc *, void *, register_t *);
int	sys_setsockopt(struct proc *, void *, register_t *);
int	sys_listen(struct proc *, void *, register_t *);
int	compat_43_sys_sigvec(struct proc *, void *, register_t *);
int	compat_43_sys_sigblock(struct proc *, void *, register_t *);
int	compat_43_sys_sigsetmask(struct proc *, void *, register_t *);
int	sys_sigsuspend(struct proc *, void *, register_t *);
int	compat_43_sys_sigstack(struct proc *, void *, register_t *);
int	compat_43_sys_recvmsg(struct proc *, void *, register_t *);
int	compat_43_sys_sendmsg(struct proc *, void *, register_t *);
int	sys_gettimeofday(struct proc *, void *, register_t *);
int	sys_getrusage(struct proc *, void *, register_t *);
int	sys_getsockopt(struct proc *, void *, register_t *);
int	sys_readv(struct proc *, void *, register_t *);
int	sys_writev(struct proc *, void *, register_t *);
int	sys_settimeofday(struct proc *, void *, register_t *);
int	sys_fchown(struct proc *, void *, register_t *);
int	sys_fchmod(struct proc *, void *, register_t *);
int	compat_43_sys_recvfrom(struct proc *, void *, register_t *);
int	sys_setreuid(struct proc *, void *, register_t *);
int	sys_setregid(struct proc *, void *, register_t *);
int	sys_rename(struct proc *, void *, register_t *);
int	compat_43_sys_truncate(struct proc *, void *, register_t *);
int	compat_43_sys_ftruncate(struct proc *, void *, register_t *);
int	sys_flock(struct proc *, void *, register_t *);
int	sys_mkfifo(struct proc *, void *, register_t *);
int	sys_sendto(struct proc *, void *, register_t *);
int	sys_shutdown(struct proc *, void *, register_t *);
int	sys_socketpair(struct proc *, void *, register_t *);
int	sys_mkdir(struct proc *, void *, register_t *);
int	sys_rmdir(struct proc *, void *, register_t *);
int	sys_utimes(struct proc *, void *, register_t *);
int	sys_adjtime(struct proc *, void *, register_t *);
int	compat_43_sys_getpeername(struct proc *, void *, register_t *);
int	compat_43_sys_gethostid(struct proc *, void *, register_t *);
int	compat_43_sys_sethostid(struct proc *, void *, register_t *);
int	compat_43_sys_getrlimit(struct proc *, void *, register_t *);
int	compat_43_sys_setrlimit(struct proc *, void *, register_t *);
int	compat_43_sys_killpg(struct proc *, void *, register_t *);
int	sys_setsid(struct proc *, void *, register_t *);
int	sys_quotactl(struct proc *, void *, register_t *);
int	compat_43_sys_quota(struct proc *, void *, register_t *);
int	compat_43_sys_getsockname(struct proc *, void *, register_t *);
#if defined(NFSCLIENT) || defined(NFSSERVER)
int	sys_nfssvc(struct proc *, void *, register_t *);
#else
#endif
int	compat_43_sys_getdirentries(struct proc *, void *, register_t *);
int	compat_25_sys_statfs(struct proc *, void *, register_t *);
int	compat_25_sys_fstatfs(struct proc *, void *, register_t *);
int	sys_getfh(struct proc *, void *, register_t *);
int	compat_09_sys_getdomainname(struct proc *, void *, register_t *);
int	compat_09_sys_setdomainname(struct proc *, void *, register_t *);
int	compat_09_sys_uname(struct proc *, void *, register_t *);
int	sys_sysarch(struct proc *, void *, register_t *);
#if defined(SYSVSEM) && !defined(__LP64__)
int	compat_10_sys_semsys(struct proc *, void *, register_t *);
#else
#endif
#if defined(SYSVMSG) && !defined(__LP64__)
int	compat_10_sys_msgsys(struct proc *, void *, register_t *);
#else
#endif
#if defined(SYSVSHM) && !defined(__LP64__)
int	compat_10_sys_shmsys(struct proc *, void *, register_t *);
#else
#endif
int	sys_pread(struct proc *, void *, register_t *);
int	sys_pwrite(struct proc *, void *, register_t *);
int	sys_setgid(struct proc *, void *, register_t *);
int	sys_setegid(struct proc *, void *, register_t *);
int	sys_seteuid(struct proc *, void *, register_t *);
int	compat_35_sys_stat(struct proc *, void *, register_t *);
int	compat_35_sys_fstat(struct proc *, void *, register_t *);
int	compat_35_sys_lstat(struct proc *, void *, register_t *);
int	sys_pathconf(struct proc *, void *, register_t *);
int	sys_fpathconf(struct proc *, void *, register_t *);
int	sys_swapctl(struct proc *, void *, register_t *);
int	sys_getrlimit(struct proc *, void *, register_t *);
int	sys_setrlimit(struct proc *, void *, register_t *);
int	sys_getdirentries(struct proc *, void *, register_t *);
int	sys_mmap(struct proc *, void *, register_t *);
int	sys_lseek(struct proc *, void *, register_t *);
int	sys_truncate(struct proc *, void *, register_t *);
int	sys_ftruncate(struct proc *, void *, register_t *);
int	sys___sysctl(struct proc *, void *, register_t *);
int	sys_mlock(struct proc *, void *, register_t *);
int	sys_munlock(struct proc *, void *, register_t *);
int	sys_futimes(struct proc *, void *, register_t *);
int	sys_getpgid(struct proc *, void *, register_t *);
int	sys_xfspioctl(struct proc *, void *, register_t *);
#ifdef LKM
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
int	sys_lkmnosys(struct proc *, void *, register_t *);
#else	/* !LKM */
#endif	/* !LKM */
#ifdef SYSVSEM
int	compat_23_sys___semctl(struct proc *, void *, register_t *);
int	sys_semget(struct proc *, void *, register_t *);
int	compat_35_sys_semop(struct proc *, void *, register_t *);
#else
#endif
#ifdef SYSVMSG
int	compat_23_sys_msgctl(struct proc *, void *, register_t *);
int	sys_msgget(struct proc *, void *, register_t *);
int	sys_msgsnd(struct proc *, void *, register_t *);
int	sys_msgrcv(struct proc *, void *, register_t *);
#else
#endif
#ifdef SYSVSHM
int	sys_shmat(struct proc *, void *, register_t *);
int	compat_23_sys_shmctl(struct proc *, void *, register_t *);
int	sys_shmdt(struct proc *, void *, register_t *);
int	compat_35_sys_shmget(struct proc *, void *, register_t *);
#else
#endif
int	sys_clock_gettime(struct proc *, void *, register_t *);
int	sys_clock_settime(struct proc *, void *, register_t *);
int	sys_clock_getres(struct proc *, void *, register_t *);
int	sys_nanosleep(struct proc *, void *, register_t *);
int	sys_minherit(struct proc *, void *, register_t *);
int	sys_rfork(struct proc *, void *, register_t *);
int	sys_poll(struct proc *, void *, register_t *);
int	sys_issetugid(struct proc *, void *, register_t *);
int	sys_lchown(struct proc *, void *, register_t *);
int	sys_getsid(struct proc *, void *, register_t *);
int	sys_msync(struct proc *, void *, register_t *);
#ifdef SYSVSEM
int	compat_35_sys___semctl(struct proc *, void *, register_t *);
#else
#endif
#ifdef SYSVSHM
int	compat_35_sys_shmctl(struct proc *, void *, register_t *);
#else
#endif
#ifdef SYSVMSG
int	compat_35_sys_msgctl(struct proc *, void *, register_t *);
#else
#endif
int	sys_getfsstat(struct proc *, void *, register_t *);
int	sys_statfs(struct proc *, void *, register_t *);
int	sys_fstatfs(struct proc *, void *, register_t *);
int	sys_pipe(struct proc *, void *, register_t *);
int	sys_fhopen(struct proc *, void *, register_t *);
int	compat_35_sys_fhstat(struct proc *, void *, register_t *);
int	sys_fhstatfs(struct proc *, void *, register_t *);
int	sys_preadv(struct proc *, void *, register_t *);
int	sys_pwritev(struct proc *, void *, register_t *);
int	sys_kqueue(struct proc *, void *, register_t *);
int	sys_kevent(struct proc *, void *, register_t *);
int	sys_mlockall(struct proc *, void *, register_t *);
int	sys_munlockall(struct proc *, void *, register_t *);
int	sys_getpeereid(struct proc *, void *, register_t *);
int	sys_getresuid(struct proc *, void *, register_t *);
int	sys_setresuid(struct proc *, void *, register_t *);
int	sys_getresgid(struct proc *, void *, register_t *);
int	sys_setresgid(struct proc *, void *, register_t *);
int	sys_mquery(struct proc *, void *, register_t *);
int	sys_closefrom(struct proc *, void *, register_t *);
int	sys_sigaltstack(struct proc *, void *, register_t *);
#ifdef SYSVSHM
int	sys_shmget(struct proc *, void *, register_t *);
#else
#endif
#ifdef SYSVSEM
int	sys_semop(struct proc *, void *, register_t *);
#else
#endif
int	sys_stat(struct proc *, void *, register_t *);
int	sys_fstat(struct proc *, void *, register_t *);
int	sys_lstat(struct proc *, void *, register_t *);
int	sys_fhstat(struct proc *, void *, register_t *);
#ifdef SYSVSEM
int	sys___semctl(struct proc *, void *, register_t *);
#else
#endif
#ifdef SYSVSHM
int	sys_shmctl(struct proc *, void *, register_t *);
#else
#endif
#ifdef SYSVMSG
int	sys_msgctl(struct proc *, void *, register_t *);
#else
#endif
int	sys_sched_yield(struct proc *, void *, register_t *);
#ifdef RTHREADS
int	sys_getthrid(struct proc *, void *, register_t *);
int	sys_thrsleep(struct proc *, void *, register_t *);
int	sys_thrwakeup(struct proc *, void *, register_t *);
int	sys_threxit(struct proc *, void *, register_t *);
int	sys_thrsigdivert(struct proc *, void *, register_t *);
#else
#endif
int	sys___getcwd(struct proc *, void *, register_t *);
int	sys_adjfreq(struct proc *, void *, register_t *);
