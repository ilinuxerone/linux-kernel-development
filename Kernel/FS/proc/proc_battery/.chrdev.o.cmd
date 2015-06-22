cmd_/home/kylin/chrdev3.1-final/proc_battery/chrdev.o := gcc -Wp,-MD,/home/kylin/chrdev3.1-final/proc_battery/.chrdev.o.d  -nostdinc -isystem /usr/lib/gcc/sparc64-redhat-linux/4.4.3/include -Iinclude  -I/usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include -include include/linux/autoconf.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -Os -m64 -pipe -mno-fpu -mcpu=niagara2 -mcmodel=medlow -ffixed-g4 -ffixed-g5 -fcall-used-g7 -Wno-sign-compare -Wa,--undeclared-regs -mtune=ultrasparc3 -Wframe-larger-than=2048 -fno-stack-protector -fomit-frame-pointer -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-dwarf2-cfi-asm -fconserve-stack  -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(chrdev)"  -D"KBUILD_MODNAME=KBUILD_STR(chrdev)"  -c -o /home/kylin/chrdev3.1-final/proc_battery/.tmp_chrdev.o /home/kylin/chrdev3.1-final/proc_battery/chrdev.c

deps_/home/kylin/chrdev3.1-final/proc_battery/chrdev.o := \
  /home/kylin/chrdev3.1-final/proc_battery/chrdev.c \
  include/linux/kernel.h \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /usr/lib/gcc/sparc64-redhat-linux/4.4.3/include/stdarg.h \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/linkage.h \
  include/linux/stddef.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/types.h \
  include/asm-generic/int-ll64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/posix_types.h \
  include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/bitops.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/bitops_64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/byteorder.h \
  include/linux/byteorder/big_endian.h \
  include/linux/swab.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/swab.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/asi.h \
    $(wildcard include/config/sparc/leon.h) \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/non-atomic.h \
  include/asm-generic/bitops/ffz.h \
  include/asm-generic/bitops/__ffs.h \
  include/asm-generic/bitops/fls.h \
  include/asm-generic/bitops/__fls.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/ffs.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/lock.h \
  include/asm-generic/bitops/find.h \
  include/asm-generic/bitops/ext2-non-atomic.h \
  include/asm-generic/bitops/le.h \
  include/asm-generic/bitops/minix.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/typecheck.h \
  include/linux/ratelimit.h \
  include/linux/param.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/param.h \
    $(wildcard include/config/hz.h) \
  include/linux/dynamic_debug.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/smp.h) \
  include/linux/module.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/sysfs.h) \
  include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  include/linux/prefetch.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/processor.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/processor_64.h \
    $(wildcard include/config/debug/spinlock.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/pstate.h \
  include/linux/const.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/ptrace.h \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/system.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/system_64.h \
    $(wildcard include/config/ft1500.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/visasm.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
    $(wildcard include/config/x86.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/irqflags.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/irqflags_64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/pil.h \
  include/asm-generic/cmpxchg-local.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/page.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/page_64.h \
    $(wildcard include/config/sparc64/page/size/8kb.h) \
    $(wildcard include/config/sparc64/page/size/64kb.h) \
    $(wildcard include/config/hugetlb/page/size/4mb.h) \
    $(wildcard include/config/hugetlb/page/size/512k.h) \
    $(wildcard include/config/hugetlb/page/size/64k.h) \
    $(wildcard include/config/hugetlb/page.h) \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  include/asm-generic/getorder.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/cache.h \
    $(wildcard include/config/sparc32.h) \
  include/linux/stat.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/stat.h \
  include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  include/linux/seqlock.h \
  include/linux/spinlock.h \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/preempt/notifiers.h) \
  include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/thread_info.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/thread_info_64.h \
    $(wildcard include/config/debug/stack/usage.h) \
  include/linux/stringify.h \
  include/linux/bottom_half.h \
  include/linux/spinlock_types.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/generic/hardirqs.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/spinlock.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/spinlock_64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/atomic.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/atomic_64.h \
  include/asm-generic/atomic-long.h \
  include/linux/spinlock_api_smp.h \
  include/linux/math64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/div64.h \
  include/asm-generic/div64.h \
  include/linux/kmod.h \
  include/linux/gfp.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/debug/vm.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  include/linux/wait.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/current.h \
    $(wildcard include/config/sparc64.h) \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/linux/init.h \
    $(wildcard include/config/hotplug.h) \
  include/linux/nodemask.h \
  include/linux/bitmap.h \
  include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/string.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/string_64.h \
  include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  include/linux/bounds.h \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/memory/hotremove.h) \
  include/linux/notifier.h \
  include/linux/errno.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/rwsem.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/rwsem-const.h \
  include/linux/srcu.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/sparsemem.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
  include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/smp.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/smp_64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/starfire.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/spitfire.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/percpu.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/percpu_64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/trap_block.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/hypervisor.h \
    $(wildcard include/config/get.h) \
    $(wildcard include/config/put.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/scratchpad.h \
  include/asm-generic/percpu.h \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/topology.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/topology_64.h \
    $(wildcard include/config/pci.h) \
  include/asm-generic/topology.h \
  include/linux/mmdebug.h \
    $(wildcard include/config/debug/virtual.h) \
  include/linux/elf.h \
  include/linux/elf-em.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/elf.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/elf_64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/uaccess.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/uaccess_64.h \
  include/asm-generic/uaccess-unaligned.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
  include/linux/kref.h \
  include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  include/linux/tracepoint.h \
  include/linux/rcupdate.h \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
  include/linux/completion.h \
  include/linux/rcutree.h \
    $(wildcard include/config/no/hz.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/local.h \
  include/asm-generic/local.h \
  include/linux/percpu.h \
    $(wildcard include/config/have/legacy/per/cpu/area.h) \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/debug/kmemleak.h) \
  include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
  include/linux/slub_def.h \
    $(wildcard include/config/slub/stats.h) \
    $(wildcard include/config/slub/debug.h) \
    $(wildcard include/config/kmemtrace.h) \
  include/linux/workqueue.h \
  include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/jiffies.h \
  include/linux/timex.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/timex.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/timex_64.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/timer.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/timer_64.h \
  include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects/free.h) \
  include/linux/kmemtrace.h \
  include/trace/events/kmem.h \
  include/trace/define_trace.h \
  include/linux/kmemleak.h \
  include/linux/pfn.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/module.h \
    $(wildcard include/config/bits.h) \
  include/trace/events/module.h \
  include/linux/cdev.h \
  include/linux/kdev_t.h \
  include/linux/semaphore.h \
  include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/security.h) \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/debug/writecount.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  include/linux/limits.h \
  include/linux/ioctl.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/ioctl.h \
  include/linux/dcache.h \
  include/linux/rculist.h \
  include/linux/path.h \
  include/linux/radix-tree.h \
  include/linux/prio_tree.h \
  include/linux/pid.h \
  include/linux/capability.h \
    $(wildcard include/config/security/file/capabilities.h) \
  include/linux/fiemap.h \
  include/linux/quota.h \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/dqblk_qtree.h \
  include/linux/nfs_fs_i.h \
  include/linux/nfs.h \
  include/linux/sunrpc/msg_prot.h \
  include/linux/inet.h \
  include/linux/fcntl.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
  include/linux/err.h \
  include/linux/proc_fs.h \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/proc/devicetree.h) \
    $(wildcard include/config/proc/kcore.h) \
    $(wildcard include/config/mmu.h) \
  include/linux/magic.h \
  include/linux/io.h \
    $(wildcard include/config/has/ioport.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/io.h \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/io_64.h \
  include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/devtmpfs.h) \
  include/linux/ioport.h \
  include/linux/klist.h \
  include/linux/pm.h \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
  /usr/src/kernels/2.6.32.20-15.8.201212.ky3.sparcv9/arch/sparc/include/asm/device.h \
  include/linux/pm_wakeup.h \
    $(wildcard include/config/pm.h) \

/home/kylin/chrdev3.1-final/proc_battery/chrdev.o: $(deps_/home/kylin/chrdev3.1-final/proc_battery/chrdev.o)

$(deps_/home/kylin/chrdev3.1-final/proc_battery/chrdev.o):
