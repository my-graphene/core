#include <graphene/chain/apply_context.hpp>
#include <graphene/chain/transaction_context.hpp>
#include <graphene/chain/exceptions.hpp>
#include <graphene/chain/transaction_object.hpp>

namespace graphene { namespace chain {

   transaction_context::transaction_context(database &d, int64_t origin, fc::microseconds max_trx_cpu_us) :
        _db(&d),
        trx_origin(origin),
        start(fc::time_point::now()),
        _deadline(start + max_trx_cpu_us),
        transaction_cpu_usage_us(0)
   {
   }

   void transaction_context::pause_billing_timer() {
       pause_time = fc::time_point::now();
   }

   void transaction_context::resume_billing_timer() {
       if(pause_time == fc::time_point()) {
           return;
       }
       pause_cpu_usage_us = (fc::time_point::now() - pause_time).count();
       pause_time = fc::time_point();
   }

   void transaction_context::checktime() const
   {
       if(pause_time > fc::time_point())
           return;

       if(pause_cpu_usage_us > 0) {
           const fc::microseconds mss(pause_cpu_usage_us);
           _deadline += mss;
           start += mss;
           pause_cpu_usage_us = 0;
       }

       auto now = fc::time_point::now();
       transaction_cpu_usage_us = (now - start).count();//TODO
	   elog( "11111111111111 (now=${n})", ("n", now) );
	   elog( "2222222222 (start=${s})", ("s", start) );
	   elog( "3333333 (now-start=${i})", ("i", now - start) );
	   elog( "4444444444 (_deadline=${d})", ("d", _deadline) );
	   elog( "55555555 (now-_deadline=${i})", ("i", now - _deadline) );
	   elog( "55555555 (transaction_cpu_usage_us=${i})", ("i", transaction_cpu_usage_us) );

       if (BOOST_UNLIKELY(now > _deadline)) {
           GRAPHENE_THROW(tx_cpu_usage_exceeded,
                          "transaction was executing for too long",
                          ("now", now)("deadline", _deadline)("start", start)("billing_timer", now - start));
       }
   }

   void transaction_context::dispatch_action(const action &a, uint64_t receiver)
   {
       apply_context acontext(db(), *this, a, optional<asset>());
       acontext.receiver = receiver;

       try {
           acontext.exec();
       } catch (...) {
           wlog("apply_context exec failed");
           throw;
       }
   }

} } /// graphene::chain
