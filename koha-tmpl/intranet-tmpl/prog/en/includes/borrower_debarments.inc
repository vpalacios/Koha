<script type="text/javascript">
   //<![CDATA[
        $(document).ready(function(e){
            $("div#reldebarments .remove_restriction").on("click",function(){
                return confirm(_("Remove restriction?"));
            });
            var mrform = $("#manual_restriction_form");
            var mrlink = $("#add_manual_restriction");
            mrform.hide();
            mrlink.on("click",function(e){
                $(this).hide();
                mrform.show();
                e.preventDefault();
            });
            $("#cancel_manual_restriction").on("click",function(e){
                mrlink.show();
                mrform.hide();
                e.preventDefault();
            });
        })
    //]]>
</script>

<div id="reldebarments">
    [% IF ( debarments.size < 1 ) %]
        <p>Patron is currently unrestricted.</p>
    [% ELSE %]
        <table>
            <thead>
                <tr>
                     <th>Type</th>
                     <th>Comment</th>
                     <th>Expiration</th>
                     [% IF ( CAN_user_borrowers ) %]
                         <th>&nbsp;</th>
                     [% END %]
                </tr>
            </thead>
            <tbody>
                [% FOREACH d IN debarments %]
                    <tr>
                        <td>
                            [% SWITCH d.type %]
                                [% CASE 'MANUAL' %]
                                    Manual
                                [% CASE 'OVERDUES' %]
                                    Overdues
                                [% CASE 'SUSPENSION' %]
                                    Suspension
                            [% END %]
                        </td>
                        <td>[% d.comment %]</td>
                        <td>[% IF d.expiration %] [% d.expiration | $KohaDates %] [% ELSE %] <i>Indefinite</i> [% END %]</td>
                        [% IF ( CAN_user_borrowers )%]
                            <td>
                                <a class="remove_restriction" href="/cgi-bin/koha/members/mod_debarment.pl?borrowernumber=[% borrowernumber %]&amp;borrower_debarment_id=[% d.borrower_debarment_id %]&amp;action=del">
                                    Remove
                                </a>
                            </td>
                        [% END %]
                    </tr>
                [% END %]
            </tbody>
        </table>
    [% END %]
    <p><a href="#" id="add_manual_restriction">Add manual restriction</a></p>
    [% IF ( CAN_user_borrowers )%]
        <form method="post" action="/cgi-bin/koha/members/mod_debarment.pl" class="clearfix">
            <input type="hidden" name="borrowernumber" value="[% borrowernumber %]" />
            <input type="hidden" name="action" value="add" />
            <fieldset class="rows" id="manual_restriction_form">
                <legend>Add manual restriction</legend>
                <ol>
                    <li><label for="rcomment">Comment:</label> <input type="text" id="rcomment" name="comment" /></li>
                    <li><label for="rexpiration">Expiration:</label> <input name="expiration" id="rexpiration" size="10" readonly="readonly" value="" class="datepicker" />
                        <a href='#' onclick="document.getElementById('expiration').value='';">Clear date</a></li>
                </ol>
            <fieldset class="action"><input type="submit" value="Add restriction" /> <a href="#" class="cancel" id="cancel_manual_restriction">Cancel</a></fieldset>
            </fieldset>
        </form>
    [% END %]
</div>
