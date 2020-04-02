#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Flags {
  uint8_t z : 1;
  uint8_t s : 1;
  uint8_t p : 1;
  uint8_t cy : 1;
  uint8_t ac : 1;
  uint8_t pad : 3;
} Flags;

typedef struct State8080 {
  uint8_t a;
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t h;
  uint8_t l;
  uint16_t w; //wz
  uint16_t sp;
  uint16_t pc;
  uint8_t* memory;
  struct Flags cc;
  uint8_t int_enable;
} State8080;

uint8_t parity(int x, int size)
{
	int i;
	int p = 0;
	x = (x & ((1<<size)-1));  // 1 << 0xff = 0xfe; 0xfe - 1 = 0xfd
	for (i=0; i<size; i++)
	{
		if (x & 0x1) p++;
		x = x >> 1;
	}
	return (0 == (p & 0x1));
}

void UnimplementedInstruction(State8080* state) {
  printf("error: unimplemented instruction\n");
  exit(1);
}

void Emulate8080p(State8080* state) {
  unsigned char* opcode = &state->memory[state->pc];

  switch (*opcode) {
    case 0x00:
      break;
    case 0x01:
      state->b = opcode[2];
      state->c = opcode[1];
      state->pc+=2;
      break;
    case 0x02:
      state->memory[(state->b << 8) | state->c] = state->a;
      break;
    case 0x03:
      UnimplementedInstruction(state);
      break;
    case 0x04:
      UnimplementedInstruction(state);
      break;
    case 0x05:
      UnimplementedInstruction(state);
      break;
    case 0x06:
      state->b = opcode[1];
      state->pc++;
      break;
    case 0x07:
      UnimplementedInstruction(state);
      break;
    case 0x08:
      UnimplementedInstruction(state);
      break;
    case 0x09:
      UnimplementedInstruction(state);
      break;
    case 0x0a:
      state->a = state->memory[(state->b << 8) | state->c];
      break;
    case 0x0b:
      UnimplementedInstruction(state);
      break;
    case 0x0c:
      UnimplementedInstruction(state);
      break;
    case 0x0d:
      UnimplementedInstruction(state);
      break;
    case 0x0e:
      state->c = opcode[1];
      state->pc++;
      break;
    case 0x0f:
      UnimplementedInstruction(state);
      break;
    case 0x10:
      UnimplementedInstruction(state);
      break;
    case 0x11:
      state->d = opcode[2];
      state->e = opcode[1];
      state->pc+=2;
      break;
    case 0x12:
      state->memory[(state->d << 8) | state->e] = state->a;
      break;
    case 0x13:
      UnimplementedInstruction(state);
      break;
    case 0x14:
      UnimplementedInstruction(state);
      break;
    case 0x15:
      UnimplementedInstruction(state);
      break;
    case 0x16:
      state->d = opcode[1];
      state->pc++;
      break;
    case 0x17:
      UnimplementedInstruction(state);
      break;
    case 0x18:
      UnimplementedInstruction(state);
      break;
    case 0x19:
      UnimplementedInstruction(state);
      break;
    case 0x1a:
      state->a = state->memory[(state->b << 8) | state->c];
      break;
    case 0x1b:
      UnimplementedInstruction(state);
      break;
    case 0x1c:
      UnimplementedInstruction(state);
      break;
    case 0x1d:
      UnimplementedInstruction(state);
      break;
    case 0x1e:
      state->e = opcode[1];
      state->pc++;
      break;
    case 0x1f:
      UnimplementedInstruction(state);
      break;
    case 0x20:
      UnimplementedInstruction(state);
      break;
    case 0x21:
      state->h = opcode[2];
      state->l = opcode[1];
      state->pc+=2;
      break;
    case 0x22:
      state->memory[(opcode[2] << 8) | opcode[1]] = state->l;
      state->memory[((opcode[2] << 8) | opcode[1])+1] = state->h;
      state->pc+=2;
      break;
    case 0x23:
      UnimplementedInstruction(state);
      break;
    case 0x24:
      UnimplementedInstruction(state);
      break;
    case 0x25:
      UnimplementedInstruction(state);
      break;
    case 0x26:
      state->h = opcode[1];
      state->pc++;
      break;
    case 0x27:
      UnimplementedInstruction(state);
      break;
    case 0x28:
      UnimplementedInstruction(state);
      break;
    case 0x29:
      UnimplementedInstruction(state);
      break;
    case 0x2a:
      state->l = state->memory[(opcode[2] << 8) | opcode[1]];
      state->h = state->memory[((opcode[2] << 8) | opcode[1])+1];
      state->pc+=2;
      break;
    case 0x2b:
      UnimplementedInstruction(state);
      break;
    case 0x2c:
      UnimplementedInstruction(state);
      break;
    case 0x2d:
      UnimplementedInstruction(state);
      break;
    case 0x2e:
      state->l = opcode[1];
      state->pc++;
      break;
    case 0x2f:
      UnimplementedInstruction(state);
      break;
    case 0x30:
      UnimplementedInstruction(state);
      break;
    case 0x31:
      state->sp = (opcode[2] << 8) | opcode[1];
      state->pc += 2;
      break;
    case 0x32:
      state->memory[(opcode[2] << 8) | opcode[1]] = state->a;
      state->pc+=2;
      break;
    case 0x33:
      UnimplementedInstruction(state);
      break;
    case 0x34:
      UnimplementedInstruction(state);
      break;
    case 0x35:
      UnimplementedInstruction(state);
      break;
    case 0x36:
      *state->memory = opcode[1];
      state->pc++;
      break;
    case 0x37:
      UnimplementedInstruction(state);
      break;
    case 0x38:
      UnimplementedInstruction(state);
      break;
    case 0x39:
      UnimplementedInstruction(state);
      break;
    case 0x3a:
      state->a = state->memory[(opcode[2] << 8) | opcode[1]];
      state->pc+=2;
      break;
    case 0x3b:
      UnimplementedInstruction(state);
      break;
    case 0x3c:
      UnimplementedInstruction(state);
      break;
    case 0x3d:
      UnimplementedInstruction(state);
      break;
    case 0x3e:
      state->a = opcode[1];
      state->pc++;
      break;
    case 0x3f:
      UnimplementedInstruction(state);
      break;
    case 0x40:
      state->b = state->b;
      break;
    case 0x41:
      state->b = state->c;
      break;
    case 0x42:
      state->b = state->d;
      break;
    case 0x43:
      state->b = state->e;
      break;
    case 0x44:
      state->b = state->h;
      break;
    case 0x45:
      state->b = state->l;
      break;
    case 0x46:
      state->b = *state->memory;
      break;
    case 0x47:
      state->b = state->a;
      break;
    case 0x48:
      state->c = state->b;
      break;
    case 0x49:
      state->c = state->c;
      break;
    case 0x4a:
      state->c = state->d;
      break;
    case 0x4b:
      state->c = state->e;
      break;
    case 0x4c:
      state->c = state->h;
      break;
    case 0x4d:
      state->c = state->l;
      break;
    case 0x4e:
      state->c = *state->memory;
      break;
    case 0x4f:
      state->c = state->a;
      break;
    case 0x50:
      state->d = state->b;
      break;
    case 0x51:
      state->d = state->c;
      break;
    case 0x52:
      state->d = state->d;
      break;
    case 0x53:
      state->d = state->e;
      break;
    case 0x54:
      state->d = state->h;
      break;
    case 0x55:
      state->d = state->l;
      break;
    case 0x56:
      state->d = *state->memory;
      break;
    case 0x57:
      state->d = state->a;
      break;
    case 0x58:
      state->e = state->b;
      break;
    case 0x59:
      state->e = state->c;
      break;
    case 0x5a:
      state->e = state->d;
      break;
    case 0x5b:
      state->e = state->e;
      break;
    case 0x5c:
      state->e = state->h;
      break;
    case 0x5d:
      state->e = state->l;
      break;
    case 0x5e:
      state->e = *state->memory;
      break;
    case 0x5f:
      state->e = state->a;
      break;
    case 0x60:
      state->h = state->b;
      break;
    case 0x61:
      state->h = state->c;
      break;
    case 0x62:
      state->h = state->d;
      break;
    case 0x63:
      state->h = state->e;
      break;
    case 0x64:
      state->h = state->h;
      break;
    case 0x65:
      state->h = state->l;
      break;
    case 0x66:
      state->h = *state->memory;
      break;
    case 0x67:
      state->h = state->a;
      break;
    case 0x68:
      state->l = state->b;
      break;
    case 0x69:
      state->l = state->c;
      break;
    case 0x6a:
      state->l = state->d;
      break;
    case 0x6b:
      state->l = state->e;
      break;
    case 0x6c:
      state->l = state->h;
      break;
    case 0x6d:
      state->l = state->l;
      break;
    case 0x6e:
      state->l = *state->memory;
      break;
    case 0x6f:
      state->l = state->a;
      break;
    case 0x70:
      *state->memory = state->b;
      break;
    case 0x71:
      *state->memory = state->c;
      break;
    case 0x72:
      *state->memory = state->d;
      break;
    case 0x73:
      *state->memory = state->e;
      break;
    case 0x74:
      *state->memory = state->h;
      break;
    case 0x75:
      *state->memory = state->l;
      break;
    case 0x76:
      UnimplementedInstruction(state);
      break;
    case 0x77:
      *state->memory = state->a;
      break;
    case 0x78:
      state->a = state->b;
      break;
    case 0x79:
      state->a = state->c;
      break;
    case 0x7a:
      state->a = state->d;
      break;
    case 0x7b:
      state->a = state->e;
      break;
    case 0x7c:
      state->a = state->h;
      break;
    case 0x7d:
      state->a = state->l;
      break;
    case 0x7e:
      state->a = *state->memory;
      break;
    case 0x7f:
      state->a = state->a;
      break;
    case 0x80:
      state->w = (uint16_t)state->a + (uint16_t)state->b;

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x81:
      state->w = (uint16_t)state->a + (uint16_t)state->c;

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x82:
      state->w = (uint16_t)state->a + (uint16_t)state->d;

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x83:
      state->w = (uint16_t)state->a + (uint16_t)state->e;

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x84:
      state->w = (uint16_t)state->a + (uint16_t)state->h;

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x85:
      state->w = (uint16_t)state->a + (uint16_t)state->l;

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x86:
      state->w = (uint16_t)state->a + (uint16_t)state->memory[(state->h << 8) | state->l];

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x87:
      state->w = (uint16_t)state->a + (uint16_t)state->a;

      state->cc.z = (state->w & 0xff);
      state->cc.s = (state->w & !0x7f);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x88:
      UnimplementedInstruction(state);
      break;
    case 0x89:
      UnimplementedInstruction(state);
      break;
    case 0x8a:
      UnimplementedInstruction(state);
      break;
    case 0x8b:
      UnimplementedInstruction(state);
      break;
    case 0x8c:
      UnimplementedInstruction(state);
      break;
    case 0x8d:
      UnimplementedInstruction(state);
      break;
    case 0x8e:
      UnimplementedInstruction(state);
      break;
    case 0x8f:
      UnimplementedInstruction(state);
      break;
    case 0x90:
      UnimplementedInstruction(state);
      break;
    case 0x91:
      UnimplementedInstruction(state);
      break;
    case 0x92:
      UnimplementedInstruction(state);
      break;
    case 0x93:
      UnimplementedInstruction(state);
      break;
    case 0x94:
      UnimplementedInstruction(state);
      break;
    case 0x95:
      UnimplementedInstruction(state);
      break;
    case 0x96:
      UnimplementedInstruction(state);
      break;
    case 0x97:
      UnimplementedInstruction(state);
      break;
    case 0x98:
      UnimplementedInstruction(state);
      break;
    case 0x99:
      UnimplementedInstruction(state);
      break;
    case 0x9a:
      UnimplementedInstruction(state);
      break;
    case 0x9b:
      UnimplementedInstruction(state);
      break;
    case 0x9c:
      UnimplementedInstruction(state);
      break;
    case 0x9d:
      UnimplementedInstruction(state);
      break;
    case 0x9e:
      UnimplementedInstruction(state);
      break;
    case 0x9f:
      UnimplementedInstruction(state);
      break;
    case 0xa0:
      UnimplementedInstruction(state);
      break;
    case 0xa1:
      UnimplementedInstruction(state);
      break;
    case 0xa2:
      UnimplementedInstruction(state);
      break;
    case 0xa3:
      UnimplementedInstruction(state);
      break;
    case 0xa4:
      UnimplementedInstruction(state);
      break;
    case 0xa5:
      UnimplementedInstruction(state);
      break;
    case 0xa6:
      UnimplementedInstruction(state);
      break;
    case 0xa7:
      UnimplementedInstruction(state);
      break;
    case 0xa8:
      UnimplementedInstruction(state);
      break;
    case 0xa9:
      UnimplementedInstruction(state);
      break;
    case 0xaa:
      UnimplementedInstruction(state);
      break;
    case 0xab:
      UnimplementedInstruction(state);
      break;
    case 0xac:
      UnimplementedInstruction(state);
      break;
    case 0xad:
      UnimplementedInstruction(state);
      break;
    case 0xae:
      UnimplementedInstruction(state);
      break;
    case 0xaf:
      UnimplementedInstruction(state);
      break;
    case 0xb0:
      UnimplementedInstruction(state);
      break;
    case 0xb1:
      UnimplementedInstruction(state);
      break;
    case 0xb2:
      UnimplementedInstruction(state);
      break;
    case 0xb3:
      UnimplementedInstruction(state);
      break;
    case 0xb4:
      UnimplementedInstruction(state);
      break;
    case 0xb5:
      UnimplementedInstruction(state);
      break;
    case 0xb6:
      UnimplementedInstruction(state);
      break;
    case 0xb7:
      UnimplementedInstruction(state);
      break;
    case 0xb8:
      UnimplementedInstruction(state);
      break;
    case 0xb9:
      UnimplementedInstruction(state);
      break;
    case 0xba:
      UnimplementedInstruction(state);
      break;
    case 0xbb:
      UnimplementedInstruction(state);
      break;
    case 0xbc:
      UnimplementedInstruction(state);
      break;
    case 0xbd:
      UnimplementedInstruction(state);
      break;
    case 0xbe:
      UnimplementedInstruction(state);
      break;
    case 0xbf:
      UnimplementedInstruction(state);
      break;
    case 0xc0:
      UnimplementedInstruction(state);
      break;
    case 0xc1:
      UnimplementedInstruction(state);
      break;
    case 0xc2:
      UnimplementedInstruction(state);
      break;
    case 0xc3:
      state->pc = (opcode[2] << 8) | opcode[1];
      break;
    case 0xc4:
      UnimplementedInstruction(state);
      break;
    case 0xc5:
      UnimplementedInstruction(state);
      break;
    case 0xc6:
      UnimplementedInstruction(state);
      break;
    case 0xc7:
      UnimplementedInstruction(state);
      break;
    case 0xc8:
      UnimplementedInstruction(state);
      break;
    case 0xc9:
      UnimplementedInstruction(state);
      break;
    case 0xca:
      UnimplementedInstruction(state);
      break;
    case 0xcb:
      UnimplementedInstruction(state);
      break;
    case 0xcc:
      UnimplementedInstruction(state);
      break;
    case 0xcd:
      state->memory[state->sp - 1] = (state->pc + 1 >> 8);  // 18dc >> 8 = 0018
      state->memory[state->sp - 2] =
          (state->pc + 1 & 0x00ff);  // 18dc & 0x00ff = 00dc
      state->sp -= 2;
      state->pc =
          (opcode[2] << 8) | opcode[1];  // 19 << 8 = 1900; 1900 | 56 = 1956
      break;
    case 0xce:
      UnimplementedInstruction(state);
      break;
    case 0xcf:
      UnimplementedInstruction(state);
      break;
    case 0xd0:
      UnimplementedInstruction(state);
      break;
    case 0xd1:
      UnimplementedInstruction(state);
      break;
    case 0xd2:
      UnimplementedInstruction(state);
      break;
    case 0xd3:
      UnimplementedInstruction(state);
      break;
    case 0xd4:
      UnimplementedInstruction(state);
      break;
    case 0xd5:
      UnimplementedInstruction(state);
      break;
    case 0xd6:
      UnimplementedInstruction(state);
      break;
    case 0xd7:
      UnimplementedInstruction(state);
      break;
    case 0xd8:
      UnimplementedInstruction(state);
      break;
    case 0xd9:
      UnimplementedInstruction(state);
      break;
    case 0xda:
      UnimplementedInstruction(state);
      break;
    case 0xdb:
      UnimplementedInstruction(state);
      break;
    case 0xdc:
      UnimplementedInstruction(state);
      break;
    case 0xdd:
      UnimplementedInstruction(state);
      break;
    case 0xde:
      UnimplementedInstruction(state);
      break;
    case 0xdf:
      UnimplementedInstruction(state);
      break;
    case 0xe0:
      UnimplementedInstruction(state);
      break;
    case 0xe1:
      UnimplementedInstruction(state);
      break;
    case 0xe2:
      UnimplementedInstruction(state);
      break;
    case 0xe3:
      UnimplementedInstruction(state);
      break;
    case 0xe4:
      UnimplementedInstruction(state);
      break;
    case 0xe5:
      UnimplementedInstruction(state);
      break;
    case 0xe6:
      UnimplementedInstruction(state);
      break;
    case 0xe7:
      UnimplementedInstruction(state);
      break;
    case 0xe8:
      UnimplementedInstruction(state);
      break;
    case 0xe9:
      UnimplementedInstruction(state);
      break;
    case 0xea:
      UnimplementedInstruction(state);
      break;
    case 0xeb:
      state->w = state->h;
      state->h = state->d;
      state->d = state->w;
      state->w = state->l;
      state->l = state->e;
      state->e = state->w;
      break;
    case 0xec:
      UnimplementedInstruction(state);
      break;
    case 0xed:
      UnimplementedInstruction(state);
      break;
    case 0xee:
      UnimplementedInstruction(state);
      break;
    case 0xef:
      UnimplementedInstruction(state);
      break;
    case 0xf0:
      UnimplementedInstruction(state);
      break;
    case 0xf1:
      UnimplementedInstruction(state);
      break;
    case 0xf2:
      UnimplementedInstruction(state);
      break;
    case 0xf3:
      UnimplementedInstruction(state);
      break;
    case 0xf4:
      UnimplementedInstruction(state);
      break;
    case 0xf5:
      UnimplementedInstruction(state);
      break;
    case 0xf6:
      UnimplementedInstruction(state);
      break;
    case 0xf7:
      UnimplementedInstruction(state);
      break;
    case 0xf8:
      UnimplementedInstruction(state);
      break;
    case 0xf9:
      UnimplementedInstruction(state);
      break;
    case 0xfa:
      UnimplementedInstruction(state);
      break;
    case 0xfb:
      UnimplementedInstruction(state);
      break;
    case 0xfc:
      UnimplementedInstruction(state);
      break;
    case 0xfd:
      UnimplementedInstruction(state);
      break;
    case 0xfe:
      UnimplementedInstruction(state);
      break;
    case 0xff:
      UnimplementedInstruction(state);
      break;
  }

  printf("%02x\n", *opcode);
  state->pc += 1;
}

int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "rb");
  if (f == NULL) {
    printf("error: couldn't open %s\n", argv[1]);
    exit(1);
  }

  State8080 p8080;

  fseek(f, 0L, SEEK_END);
  int fsize = ftell(f);
  fseek(f, 0L, SEEK_SET);

  p8080.memory = malloc(fsize);

  fread(p8080.memory, fsize, 1, (FILE*)f);
  fclose(f);

  p8080.pc = 0;
  while (p8080.pc < fsize) {
    Emulate8080p(&p8080);
  }

  return 0;
}