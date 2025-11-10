kernel_source_files := $(shell find src/impl/kernel -name *.c)
kernel_object_files := $(patsubst src/impl/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find src/impl/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/impl/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/impl/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/impl/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

# Reguła dla C (Kernel)
$(kernel_object_files): build/kernel/%.o : src/impl/kernel/%.c
	@echo "  [CC]  $<"
	@mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/intf -ffreestanding $< -o $@

# Reguła dla C (x86_64)
$(x86_64_c_object_files): build/x86_64/%.o : src/impl/x86_64/%.c
	@echo "  [CC]  $<"
	@mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/intf -ffreestanding $< -o $@

# Reguła dla ASM (x86_64)
$(x86_64_asm_object_files): build/x86_64/%.o : src/impl/x86_64/%.asm
	@echo "  [AS]  $<"
	@mkdir -p $(dir $@) && \
	nasm -f elf64 $< -o $@

.PHONY: build-x86_64 clean
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	@echo "  [LD]  dist/x86_64/kernel.bin"
	@mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) 2> /dev/null
	@echo "  [ISO] dist/x86_64/kernel.iso"
	@cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso > /dev/null 2>&1

clean:
	@echo "  [CLEAN] Cleaing a build files"
	@rm -rf build dist