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
      state->b++;
      state->c++;
      break;
    case 0x04:
      state->b++;

      state->cc.z = ((state->b & 0xff) == 0);
      state->cc.s = ((state->b & !0x7f) != 0);
      state->cc.p = parity(state->b, 0xff);
      break;
    case 0x05:
      state->b--;

      state->cc.z = ((state->b & 0xff) == 0);
      state->cc.s = ((state->b & !0x7f) != 0);
      state->cc.p = parity(state->b, 0xff);
      break;
    case 0x06:
      state->b = opcode[1];
      state->pc++;
      break;
    case 0x07:
      state->w = state->a;
      state->w <<= 1;
      state->w += (state->w > 0xff);
      state->a = state->w & 0xff;

      state->cc.cy = (state->w > 0xff);
      break;
    case 0x08:
      UnimplementedInstruction(state);
      break;
    case 0x09:
      uint32_t result = (uint32_t)((state->h << 8) + state->l) + (uint32_t)((state->b << 8) + state->c);

      state->cc.cy = (result > 0xffff);

      state->h = (result & 0xff00) >> 8;
      state->l = (result & 0xff);
      break;
    case 0x0a:
      state->a = state->memory[(state->b << 8) | state->c];
      break;
    case 0x0b:
      state->b--;
      state->c--;
      break;
    case 0x0c:
      state->c++;

      state->cc.z = ((state->c & 0xff) == 0);
      state->cc.s = ((state->c & !0x7f) != 0);
      state->cc.p = parity(state->c, 0xff);
      break;
    case 0x0d:
      state->c--;

      state->cc.z = ((state->c & 0xff) == 0);
      state->cc.s = ((state->c & !0x7f) != 0);
      state->cc.p = parity(state->c, 0xff);
      break;
    case 0x0e:
      state->c = opcode[1];
      state->pc++;
      break;
    case 0x0f:
      state->w = state->a << 8;
      state->w >>= 1;
      state->w += ((state->w & 0xff) << 8);
      state->w >>= 8;
      state->a = state->w & 0xff;

      state->cc.cy = (state->w & 0xff == 1);
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
      state->d++;
      state->e++;
      break;
    case 0x14:
      state->d++;

      state->cc.z = ((state->d & 0xff) == 0);
      state->cc.s = ((state->d & !0x7f) != 0);
      state->cc.p = parity(state->d, 0xff);
      break;
    case 0x15:
      state->d--;

      state->cc.z = ((state->d & 0xff) == 0);
      state->cc.s = ((state->d & !0x7f) != 0);
      state->cc.p = parity(state->d, 0xff);
      break;
    case 0x16:
      state->d = opcode[1];
      state->pc++;
      break;
    case 0x17:
      state->w = state->a;
      state->w <<= 1;
      state->w += (state->cc.cy);
      state->a = state->w & 0xff;

      state->cc.cy = (state->w > 0xff);
      break;
    case 0x18:
      UnimplementedInstruction(state);
      break;
    case 0x19:
      uint32_t result = (uint32_t)((state->h << 8) + state->l) + (uint32_t)((state->d << 8) + state->e);

      state->cc.cy = (result > 0xffff);

      state->h = (result & 0xff00) >> 8;
      state->l = (result & 0xff);
      break;
    case 0x1a:
      state->a = state->memory[(state->b << 8) | state->c];
      break;
    case 0x1b:
      state->d--;
      state->e--;
      break;
    case 0x1c:
      state->e++;

      state->cc.z = ((state->e & 0xff) == 0);
      state->cc.s = ((state->e & !0x7f) != 0);
      state->cc.p = parity(state->e, 0xff);
      break;
    case 0x1d:
      state->e--;

      state->cc.z = ((state->e & 0xff) == 0);
      state->cc.s = ((state->e & !0x7f) != 0);
      state->cc.p = parity(state->e, 0xff);
      break;
    case 0x1e:
      state->e = opcode[1];
      state->pc++;
      break;
    case 0x1f:
      state->w = state->a << 8;
      state->w >>= 1;
      state->w += (state->cc.cy << 15);
      state->w >>= 8;
      state->a = state->w & 0xff;

      state->cc.cy = (state->w & 0xff == 1);
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
      state->h++;
      state->l++;
      break;
    case 0x24:
      state->h++;

      state->cc.z = ((state->h & 0xff) == 0);
      state->cc.s = ((state->h & !0x7f) != 0);
      state->cc.p = parity(state->h, 0xff);
      break;
    case 0x25:
      state->h--;

      state->cc.z = ((state->h & 0xff) == 0);
      state->cc.s = ((state->h & !0x7f) != 0);
      state->cc.p = parity(state->h, 0xff);
      break;
    case 0x26:
      state->h = opcode[1];
      state->pc++;
      break;
    case 0x27:
      state->w = state->a;
      if(state->w & 0x0f > 9 || state->cc.ac) state->w += 6;
      if(state->w >> 4 & 0x0f > 9 || state->cc.cy) state->w += 6 << 4;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x28:
      UnimplementedInstruction(state);
      break;
    case 0x29:
      uint32_t result = (uint32_t)((state->h << 8) + state->l) + (uint32_t)((state->h << 8) + state->l);

      state->cc.cy = (result > 0xffff);

      state->h = (result & 0xff00) >> 8;
      state->l = (result & 0xff);
      break;
    case 0x2a:
      state->l = state->memory[(opcode[2] << 8) | opcode[1]];
      state->h = state->memory[((opcode[2] << 8) | opcode[1])+1];
      state->pc+=2;
      break;
    case 0x2b:
      state->h--;
      state->l--;
      break;
    case 0x2c:
      state->l++;

      state->cc.z = ((state->l & 0xff) == 0);
      state->cc.s = ((state->l & !0x7f) != 0);
      state->cc.p = parity(state->l, 0xff);
      break;
    case 0x2d:
      state->l--;

      state->cc.z = ((state->l & 0xff) == 0);
      state->cc.s = ((state->l & !0x7f) != 0);
      state->cc.p = parity(state->l, 0xff);
      break;
    case 0x2e:
      state->l = opcode[1];
      state->pc++;
      break;
    case 0x2f:
      state->a = ~state->a;
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
      state->sp++;
      break;
    case 0x34:
      state->memory[(state->h << 8) | state->l]++;

      state->cc.z = ((state->memory[(state->h << 8) | state->l] & 0xff) == 0);
      state->cc.s = ((state->memory[(state->h << 8) | state->l] & !0x7f) != 0);
      state->cc.p = parity(state->memory[(state->h << 8) | state->l], 0xff);
      break;
    case 0x35:
      state->memory[(state->h << 8) | state->l]--;

      state->cc.z = ((state->memory[(state->h << 8) | state->l] & 0xff) == 0);
      state->cc.s = ((state->memory[(state->h << 8) | state->l] & !0x7f) != 0);
      state->cc.p = parity(state->memory[(state->h << 8) | state->l], 0xff);
      break;
    case 0x36:
      *state->memory = opcode[1];
      state->pc++;
      break;
    case 0x37:
      state->cc.cy = 1;
      break;
    case 0x38:
      UnimplementedInstruction(state);
      break;
    case 0x39:
      uint32_t result = (uint32_t)((state->h << 8) + state->l) + (uint32_t)state->sp;

      state->cc.cy = (result > 0xffff);

      state->h = (result & 0xff00) >> 8;
      state->l = (result & 0xff);
      break;
    case 0x3a:
      state->a = state->memory[(opcode[2] << 8) | opcode[1]];
      state->pc+=2;
      break;
    case 0x3b:
      state->sp--;
      break;
    case 0x3c:
      state->a++;

      state->cc.z = ((state->a & 0xff) == 0);
      state->cc.s = ((state->a & !0x7f) != 0);
      state->cc.p = parity(state->a, 0xff);
      break;
    case 0x3d:
      state->a--;

      state->cc.z = ((state->a & 0xff) == 0);
      state->cc.s = ((state->a & !0x7f) != 0);
      state->cc.p = parity(state->a, 0xff);
      break;
    case 0x3e:
      state->a = opcode[1];
      state->pc++;
      break;
    case 0x3f:
      state->cc.cy = ~state->cc.cy;
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

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x81:
      state->w = (uint16_t)state->a + (uint16_t)state->c;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x82:
      state->w = (uint16_t)state->a + (uint16_t)state->d;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x83:
      state->w = (uint16_t)state->a + (uint16_t)state->e;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x84:
      state->w = (uint16_t)state->a + (uint16_t)state->h;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x85:
      state->w = (uint16_t)state->a + (uint16_t)state->l;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x86:
      state->w = (uint16_t)state->a + (uint16_t)state->memory[(state->h << 8) | state->l];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x87:
      state->w = (uint16_t)state->a + (uint16_t)state->a;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x88:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->b;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x89:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->c;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x8a:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->d;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x8b:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->e;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x8c:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->h;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x8d:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->l;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x8e:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->memory[(state->h << 8) | state->l];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x8f:
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)state->a;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x90:
      state->w = (uint16_t)state->a - (uint16_t)state->b;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x91:
      state->w = (uint16_t)state->a - (uint16_t)state->c;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x92:
      state->w = (uint16_t)state->a - (uint16_t)state->d;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x93:
      state->w = (uint16_t)state->a - (uint16_t)state->e;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x94:
      state->w = (uint16_t)state->a - (uint16_t)state->h;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x95:
      state->w = (uint16_t)state->a - (uint16_t)state->l;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x96:
      state->w = (uint16_t)state->a - (uint16_t)state->memory[(state->h << 8) | state->l];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x97:
      state->w = (uint16_t)state->a - (uint16_t)state->a;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x98:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->b;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x99:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->c;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x9a:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->d;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x9b:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->e;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x9c:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->h;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x9d:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->l;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x9e:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->memory[(state->h << 8) | state->l];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0x9f:
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)state->a;

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      break;
    case 0xa0:
      state->a &= state->b;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa1:
      state->a &= state->c;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa2:
      state->a &= state->d;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa3:
      state->a &= state->e;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa4:
      state->a &= state->h;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa5:
      state->a &= state->l;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa6:
      state->a &= state->memory[(state->h << 8) | state->l];

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa7:
      state->a &= state->a;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      break;
    case 0xa8:
      state->a ^= state->b;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xa9:
      state->a ^= state->c;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xaa:
      state->a ^= state->d;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xab:
      state->a ^= state->e;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xac:
      state->a ^= state->h;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xad:
      state->a ^= state->l;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xae:
      state->a ^= state->memory[(state->h << 8) | state->l];

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xaf:
      state->a ^= state->a;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb0:
      state->a |= state->b;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb1:
      state->a |= state->c;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb2:
      state->a |= state->d;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb3:
      state->a |= state->e;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb4:
      state->a |= state->h;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb5:
      state->a |= state->l;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb6:
      state->a |= state->memory[(state->h << 8) | state->l];

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb7:
      state->a |= state->a;

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;
      break;
    case 0xb8:
      state->w = (uint16_t)state->a - (uint16_t)state->b;

      state->cc.z = (state->w == state->b);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->b);
      break;
    case 0xb9:
      state->w = (uint16_t)state->a - (uint16_t)state->c;

      state->cc.z = (state->w == state->c);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->c);
      break;
    case 0xba:
      state->w = (uint16_t)state->a - (uint16_t)state->d;

      state->cc.z = (state->w == state->d);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->d);
      break;
    case 0xbb:
      state->w = (uint16_t)state->a - (uint16_t)state->e;

      state->cc.z = (state->w == state->e);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->e);
      break;
    case 0xbc:
      state->w = (uint16_t)state->a - (uint16_t)state->h;

      state->cc.z = (state->w == state->h);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->h);
      break;
    case 0xbd:
      state->w = (uint16_t)state->a - (uint16_t)state->l;

      state->cc.z = (state->w == state->l);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->l);
      break;
    case 0xbe:
      state->w = (uint16_t)state->a - (uint16_t)state->memory[(state->h << 8) | state->l];

      state->cc.z = (state->w == state->b);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->b);;
      break;
    case 0xbf:
      state->w = (uint16_t)state->a - (uint16_t)state->a;

      state->cc.z = (state->w == state->a);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < state->a);
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
      state->w = (uint16_t)state->a + (uint16_t)opcode[1];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      state->pc++;
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
      state->w = (uint16_t)state->a + (uint16_t)state->cc.cy + (uint16_t)opcode[1];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      state->pc++;
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
      state->w = (uint16_t)state->a - (uint16_t)opcode[1];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      state->pc++;
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
      state->w = (uint16_t)state->a - (uint16_t)state->cc.cy - (uint16_t)opcode[1];

      state->cc.z = ((state->w & 0xff) == 0);
      state->cc.s = ((state->w & !0x7f) != 0);
      state->cc.cy = (state->w > 0xff);
      state->cc.p = parity(state->w, 0xff);

      state->a = state->w & 0xff;
      state->pc++;
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
      state->a &= opcode[1];

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;

      state->pc++;
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
      state->a ^= opcode[1];

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;

      state->pc++;
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
      state->a |= opcode[1];

      state->cc.z = (state->a == 0);
      state->cc.s = (state->a & !0x7f != 0);
      state->cc.cy = 0;
      state->cc.p = parity (state->a, 8);
      state->cc.ac = 0;

      state->pc++;
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
      state->w = (uint16_t)state->a - (uint16_t)opcode[1];

      state->cc.z = (state->w == opcode[1]);
      state->cc.s = (state->w & !0x7f != 0);
      state->cc.p = parity (state->w, 0xff);
      state->cc.cy = (state->w < opcode[1]);

      state->pc++;
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