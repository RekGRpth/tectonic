/* tectonic/inimisc.c -- random routines originally in xetexini.c
   Copyright 2016 The Tectonic Project
   Licensed under the MIT License.
*/

#include <tectonic/tectonic.h>
#include <tectonic/internals.h>
#include <tectonic/xetexd.h>
#include <tectonic/stubs.h>


void
print_ln(void)
{
    switch (selector) {
    case 19:
	putc('\n', stdout);
	putc('\n', log_file);
	term_offset = 0;
	file_offset = 0;
        break;
    case 18:
	putc('\n', log_file);
	file_offset = 0;
        break;
    case 17:
	putc('\n', stdout);
	term_offset = 0;
        break;
    case 16:
    case 20:
    case 21:
        break;
    default:
        putc('\n', write_file[selector]);
        break;
    }
}


/*:1663*/
boolean
get_strings_started(void)
{
    pool_ptr = 0;
    str_ptr = 0;
    str_start[0] = 0;
    str_ptr = 65536L /*too_big_char*/;
    str_start[(str_ptr) - 65536L] = pool_ptr;

    if (loadpoolstrings(pool_size - string_vacancies) == 0) {
        fprintf(stdout, "%s\n", "! You have to increase POOLSIZE.");
        return false;
    }

    return true;
}

/*:1001*/

void
line_break(boolean d)
{
    memory_word *mem = zmem, *eqtb = zeqtb;
    boolean auto_breaking;
    halfword prev_p;
    halfword q, r, s, prev_s;
    internal_font_number f;
    small_number j;
    UnicodeScalar c;
    integer l;
    integer i;

    pack_begin_line = cur_list.ml_field;
    mem[mem_top - 3].hh.v.RH = mem[cur_list.head_field].hh.v.RH;
    if ((cur_list.tail_field >= hi_mem_min)) {
        mem[cur_list.tail_field].hh.v.RH = new_penalty(10000 /*inf_penalty */ );
        cur_list.tail_field = mem[cur_list.tail_field].hh.v.RH;
    } else if (mem[cur_list.tail_field].hh.u.B0 != 10 /*glue_node */ ) {
        mem[cur_list.tail_field].hh.v.RH = new_penalty(10000 /*inf_penalty */ );
        cur_list.tail_field = mem[cur_list.tail_field].hh.v.RH;
    } else {
        mem[cur_list.tail_field].hh.u.B0 = 12 /*penalty_node */ ;
        delete_glue_ref(mem[cur_list.tail_field + 1].hh.v.LH);
        flush_node_list(mem[cur_list.tail_field + 1].hh.v.RH);
        mem[cur_list.tail_field + 1].cint = 10000 /*inf_penalty */ ;
    }
    mem[cur_list.tail_field].hh.v.RH = new_param_glue(14 /*par_fill_skip_code */ );
    last_line_fill = mem[cur_list.tail_field].hh.v.RH;
    init_cur_lang = cur_list.pg_field % 65536L;
    init_l_hyf = cur_list.pg_field / 4194304L;
    init_r_hyf = (cur_list.pg_field / 65536L) % 64;
    pop_nest();
    no_shrink_error_yet = true;
    if ((mem[eqtb[2252247L /*glue_base 7 */ ].hh.v.RH].hh.u.B1 != 0 /*normal */ )
        && (mem[eqtb[2252247L /*glue_base 7 */ ].hh.v.RH + 3].cint != 0)) {
        eqtb[2252247L /*glue_base 7 */ ].hh.v.RH = finite_shrink(eqtb[2252247L /*glue_base 7 */ ].hh.v.RH);
    }
    if ((mem[eqtb[2252248L /*glue_base 8 */ ].hh.v.RH].hh.u.B1 != 0 /*normal */ )
        && (mem[eqtb[2252248L /*glue_base 8 */ ].hh.v.RH + 3].cint != 0)) {
        eqtb[2252248L /*glue_base 8 */ ].hh.v.RH = finite_shrink(eqtb[2252248L /*glue_base 8 */ ].hh.v.RH);
    }
    q = eqtb[2252247L /*glue_base 7 */ ].hh.v.RH;
    r = eqtb[2252248L /*glue_base 8 */ ].hh.v.RH;
    background[1] = mem[q + 1].cint + mem[r + 1].cint;
    background[2] = 0;
    background[3] = 0;
    background[4] = 0;
    background[5] = 0;
    background[2 + mem[q].hh.u.B0] = mem[q + 2].cint;
    background[2 + mem[r].hh.u.B0] = background[2 + mem[r].hh.u.B0] + mem[r + 2].cint;
    background[6] = mem[q + 3].cint + mem[r + 3].cint;
    do_last_line_fit = false;
    active_node_size = 3 /*active_node_size_normal */ ;
    if (eqtb[8938804L /*int_base 64 */ ].cint > 0) {
        q = mem[last_line_fill + 1].hh.v.LH;
        if ((mem[q + 2].cint > 0) && (mem[q].hh.u.B0 > 0 /*normal */ )) {

            if ((background[3] == 0) && (background[4] == 0) && (background[5] == 0)) {
                do_last_line_fit = true;
                active_node_size = 5 /*active_node_size_extended */ ;
                fill_width[0] = 0;
                fill_width[1] = 0;
                fill_width[2] = 0;
                fill_width[mem[q].hh.u.B0 - 1] = mem[q + 2].cint;
            }
        }
    }
    minimum_demerits = 1073741823L;
    minimal_demerits[3 /*tight_fit */ ] = 1073741823L;
    minimal_demerits[2 /*decent_fit */ ] = 1073741823L;
    minimal_demerits[1 /*loose_fit */ ] = 1073741823L;
    minimal_demerits[0 /*very_loose_fit */ ] = 1073741823L;
    if (eqtb[2252771L /*par_shape_loc */ ].hh.v.RH == -268435455L) {

        if (eqtb[10053209L /*dimen_base 17 */ ].cint == 0) {
            last_special_line = 0;
            second_width = eqtb[10053195L /*dimen_base 3 */ ].cint;
            second_indent = 0;
        } else {                /*878: */

            last_special_line = abs(eqtb[8938781L /*int_base 41 */ ].cint);
            if (eqtb[8938781L /*int_base 41 */ ].cint < 0) {
                first_width = eqtb[10053195L /*dimen_base 3 */ ].cint - abs(eqtb[10053209L /*dimen_base 17 */ ].cint);
                if (eqtb[10053209L /*dimen_base 17 */ ].cint >= 0)
                    first_indent = eqtb[10053209L /*dimen_base 17 */ ].cint;
                else
                    first_indent = 0;
                second_width = eqtb[10053195L /*dimen_base 3 */ ].cint;
                second_indent = 0;
            } else {

                first_width = eqtb[10053195L /*dimen_base 3 */ ].cint;
                first_indent = 0;
                second_width = eqtb[10053195L /*dimen_base 3 */ ].cint - abs(eqtb[10053209L /*dimen_base 17 */ ].cint);
                if (eqtb[10053209L /*dimen_base 17 */ ].cint >= 0)
                    second_indent = eqtb[10053209L /*dimen_base 17 */ ].cint;
                else
                    second_indent = 0;
            }
        }
    } else {

        last_special_line = mem[eqtb[2252771L /*par_shape_loc */ ].hh.v.RH].hh.v.LH - 1;
        second_width = mem[eqtb[2252771L /*par_shape_loc */ ].hh.v.RH + 2 * (last_special_line + 1)].cint;
        second_indent = mem[eqtb[2252771L /*par_shape_loc */ ].hh.v.RH + 2 * last_special_line + 1].cint;
    }
    if (eqtb[8938759L /*int_base 19 */ ].cint == 0)
        easy_line = last_special_line;
    else
        easy_line = 1073741823L /*:877 */ ;
    threshold = eqtb[8938740L /*int_base 0 */ ].cint;
    if (threshold >= 0) {
        second_pass = false;
        final_pass = false;
    } else {

        threshold = eqtb[8938741L /*int_base 1 */ ].cint;
        second_pass = true;
        final_pass = (eqtb[10053212L /*dimen_base 20 */ ].cint <= 0);
    }
    while (true) {

        if (threshold > 10000 /*inf_bad */ )
            threshold = 10000 /*inf_bad */ ;
        if (second_pass) {      /*920: */
            if (trie_not_ready)
                init_trie();

            cur_lang = init_cur_lang;
            l_hyf = init_l_hyf;
            r_hyf = init_r_hyf;
            if (trie_trc[hyph_start + cur_lang] != cur_lang)
                hyph_index = 0;
            else
                hyph_index = trie_trl[hyph_start + cur_lang];
        }
        q = get_node(active_node_size);
        mem[q].hh.u.B0 = 0 /*unhyphenated */ ;
        mem[q].hh.u.B1 = 2 /*decent_fit */ ;
        mem[q].hh.v.RH = mem_top - 7;
        mem[q + 1].hh.v.RH = -268435455L;
        mem[q + 1].hh.v.LH = cur_list.pg_field + 1;
        mem[q + 2].cint = 0;
        mem[mem_top - 7].hh.v.RH = q;
        if (do_last_line_fit) { /*1633: */
            mem[q + 3].cint = 0;
            mem[q + 4].cint = 0;
        }
        active_width[1] = background[1];
        active_width[2] = background[2];
        active_width[3] = background[3];
        active_width[4] = background[4];
        active_width[5] = background[5];
        active_width[6] = background[6];
        passive = -268435455L;
        printed_node = mem_top - 3;
        pass_number = 0;
        font_in_short_display = 0 /*font_base *//*:893 */ ;
        cur_p = mem[mem_top - 3].hh.v.RH;
        auto_breaking = true;
        {
            prev_p = cur_p;
            global_prev_p = cur_p;
        }
        first_p = cur_p;
        while ((cur_p != -268435455L) && (mem[mem_top - 7].hh.v.RH != mem_top - 7)) {   /*895: */

            if ((cur_p >= hi_mem_min)) {        /*896: */
                {
                    prev_p = cur_p;
                    global_prev_p = cur_p;
                }
                do {
                    f = mem[cur_p].hh.u.B0;
                    active_width[1] =
                        active_width[1] + font_info[width_base[f] +
                                                    font_info[char_base[f] +
                                                              effective_char(true, f, mem[cur_p].hh.u.B1)].qqqq.u.B0].cint;
                    cur_p = mem[cur_p].hh.v.RH;
                } while (!(!(cur_p >= hi_mem_min)));
            }
            switch (mem[cur_p].hh.u.B0) {
            case 0:
            case 1:
            case 2:
                active_width[1] = active_width[1] + mem[cur_p + 1].cint;
                break;
            case 8:
                if (mem[cur_p].hh.u.B1 == 4 /*language_node */ ) {
                    cur_lang = mem[cur_p + 1].hh.v.RH;
                    l_hyf = mem[cur_p + 1].hh.u.B0;
                    r_hyf = mem[cur_p + 1].hh.u.B1;
                    if (trie_trc[hyph_start + cur_lang] != cur_lang)
                        hyph_index = 0;
                    else
                        hyph_index = trie_trl[hyph_start + cur_lang];
                } else if ((mem[cur_p].hh.u.B1 == 40 /*native_word_node */ )
                           || (mem[cur_p].hh.u.B1 == 41 /*native_word_node_AT */ )
                           || (mem[cur_p].hh.u.B1 == 42 /*glyph_node */ ) || (mem[cur_p].hh.u.B1 == 43 /*pic_node */ )
                           || (mem[cur_p].hh.u.B1 == 44 /*pdf_node */ )) {
                    active_width[1] = active_width[1] + mem[cur_p + 1].cint;
                }
                break;
            case 10:
                {
                    if (auto_breaking) {
                        if ((prev_p >= hi_mem_min))
                            try_break(0, 0 /*unhyphenated */ );
                        else if ((mem[prev_p].hh.u.B0 < 9 /*math_node */ ))
                            try_break(0, 0 /*unhyphenated */ );
                        else if ((mem[prev_p].hh.u.B0 == 11 /*kern_node */ ) && (mem[prev_p].hh.u.B1 != 1 /*explicit */ ))
                            try_break(0, 0 /*unhyphenated */ );
                    }
                    if ((mem[mem[cur_p + 1].hh.v.LH].hh.u.B1 != 0 /*normal */ )
                        && (mem[mem[cur_p + 1].hh.v.LH + 3].cint != 0)) {
                        mem[cur_p + 1].hh.v.LH = finite_shrink(mem[cur_p + 1].hh.v.LH);
                    }
                    q = mem[cur_p + 1].hh.v.LH;
                    active_width[1] = active_width[1] + mem[q + 1].cint;
                    active_width[2 + mem[q].hh.u.B0] = active_width[2 + mem[q].hh.u.B0] + mem[q + 2].cint;
                    active_width[6] = active_width[6] + mem[q + 3].cint /*:897 */ ;
                    if (second_pass && auto_breaking) { /*924: */
                        prev_s = cur_p;
                        s = mem[prev_s].hh.v.RH;
                        if (s != -268435455L) {
                            while (true) {

                                if ((s >= hi_mem_min)) {
                                    c = mem[s].hh.u.B1;
                                    hf = mem[s].hh.u.B0;
                                } else if (mem[s].hh.u.B0 == 6 /*ligature_node */ ) {

                                    if (mem[s + 1].hh.v.RH == -268435455L)
                                        goto lab22;
                                    else {

                                        q = mem[s + 1].hh.v.RH;
                                        c = mem[q].hh.u.B1;
                                        hf = mem[q].hh.u.B0;
                                    }
                                } else if ((mem[s].hh.u.B0 == 11 /*kern_node */ ) && (mem[s].hh.u.B1 == 0 /*normal */ ))
                                    goto lab22;
                                else if ((mem[s].hh.u.B0 == 9 /*math_node */ ) && (mem[s].hh.u.B1 >= 4 /*L_code */ ))
                                    goto lab22;
                                else if (mem[s].hh.u.B0 == 8 /*whatsit_node */ ) {
                                    if ((mem[s].hh.u.B1 == 40 /*native_word_node */ )
                                        || (mem[s].hh.u.B1 == 41 /*native_word_node_AT */ )) {
                                        {
                                            register integer for_end;
                                            l = 0;
                                            for_end = mem[s + 4].qqqq.u.B2 - 1;
                                            if (l <= for_end)
                                                do {
                                                    c = get_native_usv(s, l);
                                                    if (eqtb[3368180L /*lc_code_base */  + c].hh.v.RH != 0) {
                                                        hf = mem[s + 4].qqqq.u.B1;
                                                        prev_s = s;
                                                        goto lab32;
                                                    }
                                                    if (c >= 65536L)
                                                        l++;
                                                }
                                                while (l++ < for_end);
                                        }
                                    }
                                    if (mem[s].hh.u.B1 == 4 /*language_node */ ) {
                                        cur_lang = mem[s + 1].hh.v.RH;
                                        l_hyf = mem[s + 1].hh.u.B0;
                                        r_hyf = mem[s + 1].hh.u.B1;
                                        if (trie_trc[hyph_start + cur_lang] != cur_lang)
                                            hyph_index = 0;
                                        else
                                            hyph_index = trie_trl[hyph_start + cur_lang];
                                    }
                                    goto lab22;
                                } else
                                    goto lab31;
                                if ((hyph_index == 0) || ((c) > 255))
                                    hc[0] = eqtb[3368180L /*lc_code_base */  + c].hh.v.RH;
                                else if (trie_trc[hyph_index + c] != c)
                                    hc[0] = 0;
                                else
                                    hc[0] = trie_tro[hyph_index + c];
                                if (hc[0] != 0) {

                                    if ((hc[0] == c) || (eqtb[8938778L /*int_base 38 */ ].cint > 0))
                                        goto lab32;
                                    else
                                        goto lab31;
                                }
 lab22:                        /*continue */ prev_s = s;
                                s = mem[prev_s].hh.v.RH;
                            }
 lab32:                        /*done2 */ hyf_char = hyphen_char[hf];
                            if (hyf_char < 0)
                                goto lab31;
                            if (hyf_char > 65535L /*biggest_char */ )
                                goto lab31;
                            ha = /*:930 */ prev_s;
                            if (l_hyf + r_hyf > max_hyphenatable_length())
                                goto lab31;
                            if ((((ha) != -268435455L && (!(ha >= hi_mem_min))
                                  && (mem[ha].hh.u.B0 == 8 /*whatsit_node */ )
                                  && ((mem[ha].hh.u.B1 == 40 /*native_word_node */ )
                                      || (mem[ha].hh.u.B1 == 41 /*native_word_node_AT */ ))))) {
                                s = mem[ha].hh.v.RH;
                                while (true) {

                                    if (!((s >= hi_mem_min)))
                                        switch (mem[s].hh.u.B0) {
                                        case 6:
                                            ;
                                            break;
                                        case 11:
                                            if (mem[s].hh.u.B1 != 0 /*normal */ )
                                                goto lab36;
                                            break;
                                        case 8:
                                        case 10:
                                        case 12:
                                        case 3:
                                        case 5:
                                        case 4:
                                            goto lab36;
                                            break;
                                        default:
                                            goto lab31;
                                            break;
                                        }
                                    s = mem[s].hh.v.RH;
                                }
 lab36:                        /*done6 *//*:926 */ ;
                                hn = 0;
 lab20:                        /*restart */  {
                                    register integer for_end;
                                    l = 0;
                                    for_end = mem[ha + 4].qqqq.u.B2 - 1;
                                    if (l <= for_end)
                                        do {
                                            c = get_native_usv(ha, l);
                                            if ((hyph_index == 0) || ((c) > 255))
                                                hc[0] = eqtb[3368180L /*lc_code_base */  + c].hh.v.RH;
                                            else if (trie_trc[hyph_index + c] != c)
                                                hc[0] = 0;
                                            else
                                                hc[0] = trie_tro[hyph_index + c];
                                            if ((hc[0] == 0)) {
                                                if ((hn > 0)) {
                                                    q = new_native_word_node(hf, mem[ha + 4].qqqq.u.B2 - l);
                                                    mem[q].hh.u.B1 = mem[ha].hh.u.B1;
                                                    {
                                                        register integer for_end;
                                                        i = l;
                                                        for_end = mem[ha + 4].qqqq.u.B2 - 1;
                                                        if (i <= for_end)
                                                            do
                                                                set_native_char(q, i - l, get_native_char(ha, i));
                                                            while (i++ < for_end);
                                                    }
                                                    set_native_metrics(q,
                                                                       (eqtb[8938814L /*eTeX_state_base 3 */ ].cint >
                                                                        0));
                                                    mem[q].hh.v.RH = mem[ha].hh.v.RH;
                                                    mem[ha].hh.v.RH = q;
                                                    mem[ha + 4].qqqq.u.B2 = l;
                                                    set_native_metrics(ha,
                                                                       (eqtb[8938814L /*eTeX_state_base 3 */ ].cint >
                                                                        0));
                                                    goto lab33;
                                                }
                                            } else if ((hn == 0) && (l > 0)) {
                                                q = new_native_word_node(hf, mem[ha + 4].qqqq.u.B2 - l);
                                                mem[q].hh.u.B1 = mem[ha].hh.u.B1;
                                                {
                                                    register integer for_end;
                                                    i = l;
                                                    for_end = mem[ha + 4].qqqq.u.B2 - 1;
                                                    if (i <= for_end)
                                                        do
                                                            set_native_char(q, i - l, get_native_char(ha, i));
                                                        while (i++ < for_end);
                                                }
                                                set_native_metrics(q,
                                                                   (eqtb[8938814L /*eTeX_state_base 3 */ ].cint > 0));
                                                mem[q].hh.v.RH = mem[ha].hh.v.RH;
                                                mem[ha].hh.v.RH = q;
                                                mem[ha + 4].qqqq.u.B2 = l;
                                                set_native_metrics(ha,
                                                                   (eqtb[8938814L /*eTeX_state_base 3 */ ].cint > 0));
                                                ha = mem[ha].hh.v.RH;
                                                goto lab20;
                                            } else if ((hn == max_hyphenatable_length()))
                                                goto lab33;
                                            else {

                                                hn++;
                                                if (c < 65536L) {
                                                    hu[hn] = c;
                                                    hc[hn] = hc[0];
                                                } else {

                                                    hu[hn] = (c - 65536L) / 1024 + 55296L;
                                                    hc[hn] = (hc[0] - 65536L) / 1024 + 55296L;
                                                    hn++;
                                                    hu[hn] = c % 1024 + 56320L;
                                                    hc[hn] = hc[0] % 1024 + 56320L;
                                                    l++;
                                                }
                                                hyf_bchar = 65536L /*too_big_char */ ;
                                            }
                                        }
                                        while (l++ < for_end);
                                }
                            } else {

                                hn = 0;
                                while (true) {

                                    if ((s >= hi_mem_min)) {
                                        if (mem[s].hh.u.B0 != hf)
                                            goto lab33;
                                        hyf_bchar = mem[s].hh.u.B1;
                                        c = hyf_bchar;
                                        if ((hyph_index == 0) || ((c) > 255))
                                            hc[0] = eqtb[3368180L /*lc_code_base */  + c].hh.v.RH;
                                        else if (trie_trc[hyph_index + c] != c)
                                            hc[0] = 0;
                                        else
                                            hc[0] = trie_tro[hyph_index + c];
                                        if (hc[0] == 0)
                                            goto lab33;
                                        if (hc[0] > max_hyph_char)
                                            goto lab33;
                                        if (hn == max_hyphenatable_length())
                                            goto lab33;
                                        hb = s;
                                        hn++;
                                        hu[hn] = c;
                                        hc[hn] = hc[0];
                                        hyf_bchar = 65536L /*too_big_char */ ;
                                    } else if (mem[s].hh.u.B0 == 6 /*ligature_node */ ) { /*932: */
                                        if (mem[s + 1].hh.u.B0 != hf)
                                            goto lab33;
                                        j = hn;
                                        q = mem[s + 1].hh.v.RH;
                                        if (q > -268435455L)
                                            hyf_bchar = mem[q].hh.u.B1;
                                        while (q > -268435455L) {

                                            c = mem[q].hh.u.B1;
                                            if ((hyph_index == 0) || ((c) > 255))
                                                hc[0] = eqtb[3368180L /*lc_code_base */  + c].hh.v.RH;
                                            else if (trie_trc[hyph_index + c] != c)
                                                hc[0] = 0;
                                            else
                                                hc[0] = trie_tro[hyph_index + c];
                                            if (hc[0] == 0)
                                                goto lab33;
                                            if (hc[0] > max_hyph_char)
                                                goto lab33;
                                            if (j == max_hyphenatable_length())
                                                goto lab33;
                                            j++;
                                            hu[j] = c;
                                            hc[j] = hc[0];
                                            q = mem[q].hh.v.RH;
                                        }
                                        hb = s;
                                        hn = j;
                                        if (odd(mem[s].hh.u.B1))
                                            hyf_bchar = font_bchar[hf];
                                        else
                                            hyf_bchar = 65536L /*too_big_char */ ;
                                    } else if ((mem[s].hh.u.B0 == 11 /*kern_node */ ) && (mem[s].hh.u.B1 == 0 /*normal */ )) {
                                        hb = s;
                                        hyf_bchar = font_bchar[hf];
                                    } else
                                        goto lab33;
                                    s = mem[s].hh.v.RH;
                                }
 lab33:                        /*done3 *//*:931 */ ;
                            }
                            if (hn < l_hyf + r_hyf)
                                goto lab31;
                            while (true) {

                                if (!((s >= hi_mem_min)))
                                    switch (mem[s].hh.u.B0) {
                                    case 6:
                                        ;
                                        break;
                                    case 11:
                                        if (mem[s].hh.u.B1 != 0 /*normal */ )
                                            goto lab34;
                                        break;
                                    case 8:
                                    case 10:
                                    case 12:
                                    case 3:
                                    case 5:
                                    case 4:
                                        goto lab34;
                                        break;
                                    case 9:
                                        if (mem[s].hh.u.B1 >= 4 /*L_code */ )
                                            goto lab34;
                                        else
                                            goto lab31;
                                        break;
                                    default:
                                        goto lab31;
                                        break;
                                    }
                                s = mem[s].hh.v.RH;
                            }
 lab34:                        /*done4 *//*:933 */ ;
                            hyphenate();
                        }
 lab31:                        /*done1 */ ;
                    }
                }
                break;
            case 11:
                if (mem[cur_p].hh.u.B1 == 1 /*explicit */ ) {
                    if (!(mem[cur_p].hh.v.RH >= hi_mem_min) && auto_breaking) {

                        if (mem[mem[cur_p].hh.v.RH].hh.u.B0 == 10 /*glue_node */ )
                            try_break(0, 0 /*unhyphenated */ );
                    }
                    active_width[1] = active_width[1] + mem[cur_p + 1].cint;
                } else
                    active_width[1] = active_width[1] + mem[cur_p + 1].cint;
                break;
            case 6:
                {
                    f = mem[cur_p + 1].hh.u.B0;
                    xtx_ligature_present = true;
                    active_width[1] =
                        active_width[1] + font_info[width_base[f] +
                                                    font_info[char_base[f] +
                                                              effective_char(true, f,
                                                                             mem[cur_p + 1].hh.u.B1)].qqqq.u.B0].cint;
                }
                break;
            case 7:
                {
                    s = mem[cur_p + 1].hh.v.LH;
                    disc_width = 0;
                    if (s == -268435455L)
                        try_break(eqtb[8938744L /*int_base 4 */ ].cint, 1 /*hyphenated */ );
                    else {

                        do {
                            /*899: */ if ((s >= hi_mem_min)) {
                                f = mem[s].hh.u.B0;
                                disc_width =
                                    disc_width + font_info[width_base[f] +
                                                           font_info[char_base[f] +
                                                                     effective_char(true, f,
                                                                                    mem[s].hh.u.B1)].qqqq.u.B0].cint;
                            } else
                                switch (mem[s].hh.u.B0) {
                                case 6:
                                    {
                                        f = mem[s + 1].hh.u.B0;
                                        xtx_ligature_present = true;
                                        disc_width =
                                            disc_width + font_info[width_base[f] +
                                                                   font_info[char_base[f] +
                                                                             effective_char(true, f,
                                                                                            mem[s +
                                                                                                1].hh.u.B1)].qqqq.u.B0].
                                            cint;
                                    }
                                    break;
                                case 0:
                                case 1:
                                case 2:
                                case 11:
                                    disc_width = disc_width + mem[s + 1].cint;
                                    break;
                                case 8:
                                    if ((mem[s].hh.u.B1 == 40 /*native_word_node */ )
                                        || (mem[s].hh.u.B1 == 41 /*native_word_node_AT */ )
                                        || (mem[s].hh.u.B1 == 42 /*glyph_node */ ) || (mem[s].hh.u.B1 == 43 /*pic_node */ )
                                        || (mem[s].hh.u.B1 == 44 /*pdf_node */ ))
                                        disc_width = disc_width + mem[s + 1].cint;
                                    else
                                        confusion(66333L /*"disc3a" */ );
                                    break;
                                default:
                                    confusion(66334L /*"disc3" */ );
                                    break;
                                }
                            s = mem[s].hh.v.RH;
                        } while (!(s == -268435455L));
                        active_width[1] = active_width[1] + disc_width;
                        try_break(eqtb[8938743L /*int_base 3 */ ].cint, 1 /*hyphenated */ );
                        active_width[1] = active_width[1] - disc_width;
                    }
                    r = mem[cur_p].hh.u.B1;
                    s = mem[cur_p].hh.v.RH;
                    while (r > 0) {

                        if ((s >= hi_mem_min)) {
                            f = mem[s].hh.u.B0;
                            active_width[1] =
                                active_width[1] + font_info[width_base[f] +
                                                            font_info[char_base[f] +
                                                                      effective_char(true, f,
                                                                                     mem[s].hh.u.B1)].qqqq.u.B0].cint;
                        } else
                            switch (mem[s].hh.u.B0) {
                            case 6:
                                {
                                    f = mem[s + 1].hh.u.B0;
                                    xtx_ligature_present = true;
                                    active_width[1] =
                                        active_width[1] + font_info[width_base[f] +
                                                                    font_info[char_base[f] +
                                                                              effective_char(true, f,
                                                                                             mem[s +
                                                                                                 1].hh.u.B1)].qqqq.u.B0].
                                        cint;
                                }
                                break;
                            case 0:
                            case 1:
                            case 2:
                            case 11:
                                active_width[1] = active_width[1] + mem[s + 1].cint;
                                break;
                            case 8:
                                if ((mem[s].hh.u.B1 == 40 /*native_word_node */ )
                                    || (mem[s].hh.u.B1 == 41 /*native_word_node_AT */ )
                                    || (mem[s].hh.u.B1 == 42 /*glyph_node */ ) || (mem[s].hh.u.B1 == 43 /*pic_node */ )
                                    || (mem[s].hh.u.B1 == 44 /*pdf_node */ ))
                                    active_width[1] = active_width[1] + mem[s + 1].cint;
                                else
                                    confusion(66335L /*"disc4a" */ );
                                break;
                            default:
                                confusion(66336L /*"disc4" */ );
                                break;
                            }
                        r--;
                        s = mem[s].hh.v.RH;
                    }
                    {
                        prev_p = cur_p;
                        global_prev_p = cur_p;
                    }
                    cur_p = s;
                    goto lab35;
                }
                break;
            case 9:
                {
                    if (mem[cur_p].hh.u.B1 < 4 /*L_code */ )
                        auto_breaking = odd(mem[cur_p].hh.u.B1);
                    {
                        if (!(mem[cur_p].hh.v.RH >= hi_mem_min) && auto_breaking) {

                            if (mem[mem[cur_p].hh.v.RH].hh.u.B0 == 10 /*glue_node */ )
                                try_break(0, 0 /*unhyphenated */ );
                        }
                        active_width[1] = active_width[1] + mem[cur_p + 1].cint;
                    }
                }
                break;
            case 12:
                try_break(mem[cur_p + 1].cint, 0 /*unhyphenated */ );
                break;
            case 4:
            case 3:
            case 5:
                ;
                break;
            default:
                confusion(66332L /*"paragraph" */ );
                break;
            }
            {
                prev_p = cur_p;
                global_prev_p = cur_p;
            }
            cur_p = mem[cur_p].hh.v.RH;
 lab35:                        /*done5 */ ;
        }
        if (cur_p == -268435455L) {     /*902: */
            try_break(-10000 /*eject_penalty */ , 1 /*hyphenated */ );
            if (mem[mem_top - 7].hh.v.RH != mem_top - 7) {
                r = mem[mem_top - 7].hh.v.RH;
                fewest_demerits = 1073741823L;
                do {
                    if (mem[r].hh.u.B0 != 2 /*delta_node */ ) {
                        if (mem[r + 2].cint < fewest_demerits) {
                            fewest_demerits = mem[r + 2].cint;
                            best_bet = r;
                        }
                    }
                    r = mem[r].hh.v.RH;
                } while (!(r == mem_top - 7));
                best_line = mem[best_bet + 1].hh.v.LH /*:903 */ ;
                if (eqtb[8938759L /*int_base 19 */ ].cint == 0)
                    goto lab30;
                {
                    r = mem[mem_top - 7].hh.v.RH;
                    actual_looseness = 0;
                    do {
                        if (mem[r].hh.u.B0 != 2 /*delta_node */ ) {
                            line_diff = mem[r + 1].hh.v.LH - best_line;
                            if (((line_diff < actual_looseness) && (eqtb[8938759L /*int_base 19 */ ].cint <= line_diff))
                                || ((line_diff > actual_looseness)
                                    && (eqtb[8938759L /*int_base 19 */ ].cint >= line_diff))) {
                                best_bet = r;
                                actual_looseness = line_diff;
                                fewest_demerits = mem[r + 2].cint;
                            } else if ((line_diff == actual_looseness) && (mem[r + 2].cint < fewest_demerits)) {
                                best_bet = r;
                                fewest_demerits = mem[r + 2].cint;
                            }
                        }
                        r = mem[r].hh.v.RH;
                    } while (!(r == mem_top - 7));
                    best_line = mem[best_bet + 1].hh.v.LH;
                }
                if ((actual_looseness == eqtb[8938759L /*int_base 19 */ ].cint) || final_pass)
                    goto lab30;
            }
        }
        q = mem[mem_top - 7].hh.v.RH;
        while (q != mem_top - 7) {

            cur_p = mem[q].hh.v.RH;
            if (mem[q].hh.u.B0 == 2 /*delta_node */ )
                free_node(q, 7 /*delta_node_size */ );
            else
                free_node(q, active_node_size);
            q = cur_p;
        }
        q = passive;
        while (q != -268435455L) {

            cur_p = mem[q].hh.v.RH;
            free_node(q, 2 /*passive_node_size */ );
            q = cur_p;
        }
        if (!second_pass) {
            threshold = eqtb[8938741L /*int_base 1 */ ].cint;
            second_pass = true;
            final_pass = (eqtb[10053212L /*dimen_base 20 */ ].cint <= 0);
        } else {
            background[2] = background[2] + eqtb[10053212L /*dimen_base 20 */ ].cint;
            final_pass = true;
        }
    }

lab30:/* done */

    if (do_last_line_fit) {     /*1641: */

        if (mem[best_bet + 3].cint == 0)
            do_last_line_fit = false;
        else {

            q = new_spec(mem[last_line_fill + 1].hh.v.LH);
            delete_glue_ref(mem[last_line_fill + 1].hh.v.LH);
            mem[q + 1].cint = mem[q + 1].cint + mem[best_bet + 3].cint - mem[best_bet + 4].cint;
            mem[q + 2].cint = 0;
            mem[last_line_fill + 1].hh.v.LH = q;
        }
    }
    post_line_break(d);
    q = mem[mem_top - 7].hh.v.RH;
    while (q != mem_top - 7) {

        cur_p = mem[q].hh.v.RH;
        if (mem[q].hh.u.B0 == 2 /*delta_node */ )
            free_node(q, 7 /*delta_node_size */ );
        else
            free_node(q, active_node_size);
        q = cur_p;
    }
    q = passive;
    while (q != -268435455L) {

        cur_p = mem[q].hh.v.RH;
        free_node(q, 2 /*passive_node_size */ );
        q = cur_p;
    }
    pack_begin_line = 0;
}


halfword
prune_page_top(halfword p, boolean s)
{
    memory_word *mem = zmem;
    halfword prev_p;
    halfword q, r;

    prev_p = mem_top - 3;
    mem[mem_top - 3].hh.v.RH = p;

    while (p != -268435455L)
        switch (mem[p].hh.u.B0) {
        case 0:
        case 1:
        case 2:
	    q = new_skip_param(10 /*split_top_skip_code */ );
	    mem[prev_p].hh.v.RH = q;
	    mem[q].hh.v.RH = p;
	    if (mem[temp_ptr + 1].cint > mem[p + 3].cint)
		mem[temp_ptr + 1].cint = mem[temp_ptr + 1].cint - mem[p + 3].cint;
	    else
		mem[temp_ptr + 1].cint = 0;
	    p = -268435455L;
            break;
        case 8:
        case 4:
        case 3:
	    prev_p = p;
	    p = mem[prev_p].hh.v.RH;
            break;
        case 10:
        case 11:
        case 12:
	    q = p;
	    p = mem[q].hh.v.RH;
	    mem[q].hh.v.RH = -268435455L;
	    mem[prev_p].hh.v.RH = p;
	    if (s) {
		if (disc_ptr[3 /*vsplit_code */ ] == -268435455L)
		    disc_ptr[3 /*vsplit_code */ ] = q;
		else
		    mem[r].hh.v.RH = q;
		r = q;
	    } else
		flush_node_list(q);
            break;
        default:
            confusion(66357L /*"pruning" */ );
            break;
        }

    return mem[mem_top - 3].hh.v.RH;
}


boolean
do_marks(small_number a, small_number l, halfword q)
{
    memory_word *mem = zmem;
    small_number i;

    if (l < 4) {
	register integer for_end;

	i = 0;
	for_end = 15;
	if (i <= for_end)
	    do {
		if (odd(i))
		    cur_ptr = mem[q + (i / 2) + 1].hh.v.RH;
		else
		    cur_ptr = mem[q + (i / 2) + 1].hh.v.LH;
		if (cur_ptr != -268435455L) {
		    if (do_marks(a, l + 1, cur_ptr)) {
			if (odd(i))
			    mem[q + (i / 2) + 1].hh.v.RH = -268435455L;
			else
			    mem[q + (i / 2) + 1].hh.v.LH = -268435455L;
			mem[q].hh.u.B1--;
		    }
		}
	    } while (i++ < for_end);

	if (mem[q].hh.u.B1 == 0) {
	    free_node(q, 33 /*index_node_size */ );
	    q = -268435455L;
        }
    } else {
        switch (a) { /*1614: */
        case 0:
            if (mem[q + 2].hh.v.RH != -268435455L) {
                delete_token_ref(mem[q + 2].hh.v.RH);
                mem[q + 2].hh.v.RH = -268435455L;
                delete_token_ref(mem[q + 3].hh.v.LH);
                mem[q + 3].hh.v.LH = -268435455L;
            }
            break;
        case 1:
            if (mem[q + 2].hh.v.LH != -268435455L) {
                if (mem[q + 1].hh.v.LH != -268435455L)
                    delete_token_ref(mem[q + 1].hh.v.LH);
                delete_token_ref(mem[q + 1].hh.v.RH);
                mem[q + 1].hh.v.RH = -268435455L;
                if (mem[mem[q + 2].hh.v.LH].hh.v.RH == -268435455L) {
                    delete_token_ref(mem[q + 2].hh.v.LH);
                    mem[q + 2].hh.v.LH = -268435455L;
                } else
                    mem[mem[q + 2].hh.v.LH].hh.v.LH++;
                mem[q + 1].hh.v.LH = mem[q + 2].hh.v.LH;
            }
            break;
        case 2:
            if ((mem[q + 1].hh.v.LH != -268435455L) && (mem[q + 1].hh.v.RH == -268435455L)) {
                mem[q + 1].hh.v.RH = mem[q + 1].hh.v.LH;
                mem[mem[q + 1].hh.v.LH].hh.v.LH++;
            }
            break;
            ;
        case 3:
            {
                register integer for_end;
                i = 0 /*top_mark_code */ ;
                for_end = 4 /*split_bot_mark_code */ ;
                if (i <= for_end)
                    do {
                        if (odd(i))
                            cur_ptr = mem[q + (i / 2) + 1].hh.v.RH;
                        else
                            cur_ptr = mem[q + (i / 2) + 1].hh.v.LH;
                        if (cur_ptr != -268435455L) {
                            delete_token_ref(cur_ptr);
                            if (odd(i))
                                mem[q + (i / 2) + 1].hh.v.RH = -268435455L;
                            else
                                mem[q + (i / 2) + 1].hh.v.LH = -268435455L;
                        }
                    }
                    while (i++ < for_end);
            }
            break;
        }

        if (mem[q + 2].hh.v.LH == -268435455L) {
            if (mem[q + 3].hh.v.LH == -268435455L) {
                free_node(q, 4 /*mark_class_node_size */ );
                q = -268435455L;
            }
        }
    }

    return (q == -268435455L);
}


void
do_assignments(void)
{
    while (true) {
        do {
            get_x_token();
        } while (!((cur_cmd != 10 /*spacer */ ) && (cur_cmd != 0 /*relax */ ) /*:422 */ ));

        if (cur_cmd <= 71 /*max_non_prefixed_command */ )
            return;

        set_box_allowed = false;
        prefixed_command();
        set_box_allowed = true;
    }
}


void
open_or_close_in(void)
{
    memory_word *eqtb = zeqtb;
    unsigned char c, n;
    integer k;

    c = cur_chr;
    scan_four_bit_int();
    n = cur_val;

    if (read_open[n] != 2 /*closed */ ) {
        u_close(read_file[n]);
        read_open[n] = 2 /*closed */ ;
    }

    if (c != 0) {
        scan_optional_equals();
        scan_file_name();
        pack_file_name(cur_name, cur_area, cur_ext);
        tex_input_type = 0;

        if (u_open_in(&read_file[n], kpse_tex_format, FOPEN_RBIN_MODE, eqtb[8938817L /*eTeX_state_base 6 */ ].cint,
		      eqtb[8938818L /*eTeX_state_base 7 */ ].cint)) {
            make_utf16_name();
            name_in_progress = true;
            begin_name();
            stop_at_space = false;
            k = 0;
            while ((k < name_length16) && (more_name(name_of_file16[k])))
                k++;
            stop_at_space = true;
            end_name();
            name_in_progress = false;
            read_open[n] = 1 /*just_open */ ;
        }
    }
}



void
new_whatsit(small_number s, small_number w)
{
    memory_word *mem = zmem;
    halfword p;

    p = get_node(w);
    mem[p].hh.u.B0 = 8 /*whatsit_node*/;
    mem[p].hh.u.B1 = s;
    mem[cur_list.tail_field].hh.v.RH = p;
    cur_list.tail_field = p;
}
